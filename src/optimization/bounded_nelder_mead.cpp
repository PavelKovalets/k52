#include <k52/optimization/bounded_nelder_mead.h>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream>

#include  <k52/common/constants.h>

using ::std::vector;
using ::k52::common::Constants;

namespace k52
{
namespace optimization
{

BoundedNelderMead::BoundedNelderMead(double l, double precision, double lower_bound, double upper_bound)
{
    lower_bound_ = lower_bound;
    upper_bound_ = upper_bound;
    precision_ = precision;
    l_ = l;
}

BoundedNelderMead* BoundedNelderMead::Clone() const
{
    return new BoundedNelderMead(l_, precision_, lower_bound_, upper_bound_);
}

std::string BoundedNelderMead::get_name() const
{
    return "Bounded Nelder Mead";
}

double BoundedNelderMead::get_lower_bound() const
{
    return lower_bound_;
}

double BoundedNelderMead::get_upper_bound() const
{
    return upper_bound_;
}

#ifdef BUILD_WITH_MPI
void BoundedNelderMead::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, l_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, precision_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, lower_bound_);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, upper_bound_);
}

void BoundedNelderMead::Receive(boost::mpi::communicator* communicator, int source)
{
    communicator->recv(source,
                       k52::parallel::mpi::constants::kCommonTag,
                       l_);
    communicator->recv(source,
                       k52::parallel::mpi::constants::kCommonTag,
                       precision_);
    communicator->recv(source,
                       k52::parallel::mpi::constants::kCommonTag,
                       lower_bound_);
    communicator->recv(source,
                       k52::parallel::mpi::constants::kCommonTag,
                       upper_bound_);
}
#endif

std::vector<double> BoundedNelderMead::FindOptimalParameters(const std::vector<double>& initial_parameters)
{
    //Iteration index
    size_t r = 0;

    //Build simplex based on initial_parameters
    vector< vector<double> > polygon = GetRegularSimplex(initial_parameters, l_);

    //count values
    vector<double> function_values = CountObjectiveFunctionValues(polygon);

    do
    {
        OutputPolygon(polygon);
        r++;

        size_t first_max_index = 0, second_max_index = 0, min_index = 0;
        //determine maximums and minimum
        GetIndexes(function_values, &first_max_index, &second_max_index, &min_index);

        double highest_value = function_values[first_max_index];
        double second_highest_value = function_values[second_max_index];
        double lowest_value = function_values[min_index];

        //determine center of mass
        vector<double> center_of_mass = GetCenterOfMass(polygon, first_max_index);

        //Reflect max point - we seek for minimum
        vector<double> reflected_point = Reflexion(center_of_mass, polygon[first_max_index]);
        CorrectByProjectingToBounds(&reflected_point);
        double reflected_point_value = CountSingleObjectiveFunctionValue(reflected_point);

        if (reflected_point_value < lowest_value)
        {
            vector<double> expanded_point = Expansion(center_of_mass, reflected_point);
            CorrectByProjectingToBounds(&expanded_point);
            double expanded_point_value = CountSingleObjectiveFunctionValue(expanded_point);

            if (expanded_point_value < reflected_point_value)
            {
                //Replace max with expanded
                polygon[first_max_index] = expanded_point;
                function_values[first_max_index] = expanded_point_value;
                continue;
            }
            else
            {
                //Replace max with reflected
                polygon[first_max_index] = reflected_point;
                function_values[first_max_index] = reflected_point_value;
                continue;
            }
        }
        else
        {
            if (reflected_point_value <= second_highest_value)
            {
                //Replace max with reflected
                polygon[first_max_index] = reflected_point;
                function_values[first_max_index] = reflected_point_value;
                continue;
            }
            else
            {
                if (reflected_point_value < highest_value)
                {
                    //Replace max with reflected
                    polygon[first_max_index] = reflected_point;
                    function_values[first_max_index] = reflected_point_value;
                    highest_value = reflected_point_value;
                }

                vector<double> contraction_point = Contraction(center_of_mass, polygon[first_max_index]);
                double contraction_point_value = CountSingleObjectiveFunctionValue(contraction_point);

                if (contraction_point_value > highest_value)
                {
                    Reduction(&polygon, min_index);
                    continue;
                }
                else
                {
                    //Replace max with contracted
                    polygon[first_max_index] = contraction_point;
                    function_values[first_max_index] = contraction_point_value;
                    continue;
                }
            }
        }
    } while (GetTerminationCriteria(r, function_values, polygon));


    size_t best_index = std::distance(function_values.begin(), std::max_element(function_values.begin(), function_values.end()));
    return polygon[best_index];
}

void BoundedNelderMead::CorrectByProjectingToBounds(vector<double>* point)
{
    for(size_t i = 0; i < point->size(); i++)
    {
        if( (*point)[i] > upper_bound_)
        {
            (*point)[i] = upper_bound_;
        }
        else if( (*point)[i] < lower_bound_)
        {
            (*point)[i] = lower_bound_;
        }
    }
}

vector<double> BoundedNelderMead::CountObjectiveFunctionValues(
    const vector< vector<double> >& parameters_values)
{
    size_t N = parameters_values.size();
    vector<double> counted_values(N);

    for(size_t i = 0; i < N; i++)
    {
        //As Nelder-Mead tends to minimize function we need to reverse it to find max
        counted_values[i] = CountObjectiveFunctionValueToMinimize(parameters_values[i]);
    }

    return counted_values;
}

double BoundedNelderMead::CountSingleObjectiveFunctionValue(
    const vector<double>& parameters)
{
    vector< vector<double> > cover(1);
    cover[0] = parameters;
    return CountObjectiveFunctionValues(cover)[0];
}

bool BoundedNelderMead::GetTerminationCriteria(
        size_t itreation_index,
        const std::vector<double>& function_values,
        const std::vector< std::vector<double> >& polygon)
{
    const size_t iterations_per_dimension = 1000;
    if (itreation_index > iterations_per_dimension * polygon[0].size())
    {
        std::cout << "WARNING: Exiting BDNM by iterations"
                " criteria!" << std::endl;
        return false;
    }

    if (WasSamePolygonBefore(polygon))
    {
        std::cout << "WARNING: Exiting BDNM because of a polygon loop,"
                " you migth have a special function behaviour." << std::endl;
        return false;
    }

    return CountDifferance(function_values) > precision_;
}

bool BoundedNelderMead::WasSamePolygonBefore(const std::vector< std::vector<double> >& polygon)
{
    bool was_same_before = false;

    for (std::list< std::vector< std::vector<double> > >::const_iterator it = previous_polygons_.begin();
         it != previous_polygons_.end();
         ++it)
    {
        if (CountPolygonDifferance(polygon, *it) < Constants::Eps)
        {
            was_same_before = true;
            break;
        }
    }

    if (previous_polygons_.size() >= max_previous_polygons_count)
    {
        previous_polygons_.pop_front();
    }
    previous_polygons_.push_back(polygon);

    return was_same_before;
}

void BoundedNelderMead::GetIndexes(const vector<double>& values, size_t* first_max_index, size_t* secound_max_index, size_t* min_index)
{
    if(values.size() < 2)
    {
        throw std::invalid_argument("values must have at least 2 elements");
    }

    if( values[0] > values[1] )
    {
        *first_max_index = 0;
        *secound_max_index = 1;
        *min_index = 1;
    }
    else
    {
        *first_max_index = 1;
        *secound_max_index = 0;
        *min_index = 0;
    }

    for (size_t i = 2; i<values.size(); i++) 
    {
        if (values[i] > values[*first_max_index]) 
        {
            *secound_max_index = *first_max_index;
            *first_max_index = i;
        } 
        else if (values[i]  > values[*secound_max_index]) 
        {
            *secound_max_index = i;
        }

        if( values[i] < values[*min_index])
        {
            *min_index = i;
        }
    }
}

vector< vector<double> > BoundedNelderMead::GetRegularSimplex(const vector<double>& base_point, double l)
{
    //Size of task
    size_t n = base_point.size();

    //For simplex points count
    double square_root_from_2 = std::sqrt(2.);
    double r1 = l * ( std::sqrt((double)(n+1)) + n - 1 ) / ( n * square_root_from_2 );
    double r2 = l * ( std::sqrt((double)(n+1)) - 1 ) / ( n * square_root_from_2 );

    vector< vector<double> > regular_simplex( n + 1 );
    regular_simplex[0] = base_point;

    for(size_t i = 1; i < n + 1; i++)
    {
        regular_simplex[i] = vector<double>(n);

        for(size_t j = 0; j < n; j++)
        {
            if( j == i - 1 )
            {
                regular_simplex[i][j] = base_point[j] + r1;
            }
            else
            {
                regular_simplex[i][j] = base_point[j] + r2;
            }
        }
    }
    return regular_simplex;
}

vector<double> BoundedNelderMead::Reflexion(const vector<double>& center_of_mass, const vector<double>& target_point)
{
    double reflection_coefficient = 1;
    vector<double> new_point (target_point.size());

    //Reflect
    for(size_t i = 0; i < target_point.size(); i++)
    {
        new_point[i] = center_of_mass[i] + reflection_coefficient * (center_of_mass[i] - target_point[i]);
    }

    return new_point;
}

vector<double> BoundedNelderMead::Expansion(const vector<double>& center_of_mass, const vector<double>& target_point)
{
    double expansion_coefficient = 2;
    vector<double> new_point (target_point.size());

    //Expand
    for(size_t i = 0; i < target_point.size(); i++)
    {
        new_point[i] = center_of_mass[i] + expansion_coefficient * (target_point[i] - center_of_mass[i]);
    }

    return new_point;
}

vector<double> BoundedNelderMead::Contraction(const vector<double>& center_of_mass, const vector<double>& target_point)
{
    double contraction_coefficient = 0.5;
    vector<double> new_point (target_point.size());

    //Contract
    for(size_t i = 0; i < target_point.size(); i++)
    {
        new_point[i] = center_of_mass[i] + contraction_coefficient * (target_point[i] - center_of_mass[i]);
    }

    return new_point;
}

void BoundedNelderMead::Reduction(vector< vector<double> >* polygon, size_t point_index)
{
    if(point_index<0 || point_index>= polygon->size())
    {
        throw std::invalid_argument("Incorrect point_index");
    }

    double reduction_coefficient = 0.5;
    size_t n = (*polygon)[0].size();

    for(size_t i = 0; i < n +1; i++)
    {
        if( i != point_index )
        {
            for(size_t j = 0; j < n; j++)
            {
                (*polygon)[i][j] = (*polygon)[point_index][j] + reduction_coefficient * ( (*polygon)[i][j]  - (*polygon)[point_index][j] );
            }
        }
    }
}

double BoundedNelderMead::CountDifferance(const vector<double>& values)
{
    double summ = 0;
    for(size_t i = 0; i < values.size(); i++)
    {
        summ += values[i];
    }
    double averadge = summ / values.size();

    double square_summ = 0;
    for(size_t i = 0; i < values.size(); i++)
    {
        double diff = values[i] - averadge;
        square_summ += diff*diff;
    }
    return sqrt( square_summ / values.size());
}

double BoundedNelderMead::CountPolygonDifferance(
        const std::vector< std::vector<double> >& polygon,
        const std::vector< std::vector<double> >& previous_polygon)
{
    double summ = 0;
    for(size_t i = 0; i < polygon.size(); i++)
    {
        for(size_t j = 0; j < polygon[i].size(); j++)
        {
            summ += std::abs(polygon[i][j] - previous_polygon[i][j]);
        }
    }
    return summ;
}

vector<double> BoundedNelderMead::GetCenterOfMass(const vector< vector<double> >& polygon, size_t point_index)
{
    if(point_index<0 || point_index>= polygon.size())
    {
        throw std::invalid_argument("Incorrect point_index");
    }
    size_t n = polygon[0].size();
    vector<double> center_of_mass(n);

    //TODO implement with valarray
    for(size_t i = 0; i < n; i++)
    {
        center_of_mass[i] = 0;

        for(size_t j = 0; j < n+1; j++)
        {
            if( j != point_index )
            {
                center_of_mass[i] += polygon[j][i];
            }
        }

        center_of_mass[i] /= n;
    }

    return center_of_mass;
}

void BoundedNelderMead::OutputPolygon(const vector< vector<double> >& polygon)
{
    std::ofstream polygon_output("polygon.plot", std::ofstream::app);
    polygon_output.precision(16);
    polygon_output<<std::endl;

    for(size_t i = 0; i < polygon.size(); i++)
    {
        for(size_t j = 0; j < polygon[i].size(); j++)
        {
            polygon_output << polygon[i][j] << " ";
        }
        polygon_output<<std::endl;
    }
}

}/* namespace optimization */
}/* namespace k52 */
