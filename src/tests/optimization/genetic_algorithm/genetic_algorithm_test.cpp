#include <iostream>
#include <math.h>
#include <ctime>
#include <limits>
#include <stdlib.h>

//OA headers
#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/identifyable_objects_manager.h>
#endif

#include <k52/common/settings_manager.h>
#include <k52/optimization/genetic_algorithm.h>
#include <k52/optimization/params/double_parameters_array.h>
#include <k52/optimization/params/continuous_parameters_array.h>

using namespace std;
using namespace k52::optimization;

const double GlobalPrecision = 0.0001;
const int GlobalNumberOfParameters = 2;
const double GlobalMinValue = GlobalPrecision;
const double GlobalMaxValue = 100;
const int GlobalThreads= 4;

class ExactDiscreteObjectiveFunction : public k52::optimization::DiscreteObjectiveFunction
{
public:

    virtual ExactDiscreteObjectiveFunction* Clone() const
    {
        return new ExactDiscreteObjectiveFunction();
    }

    double operator () (const IDiscreteParameters* const iparameters) const
    {
        const DoubleParametersArray* const parametrs = dynamic_cast<const DoubleParametersArray* const>(iparameters);

        if (!parametrs)
        {
            throw std::logic_error("ExactDiscreteObjectiveFunction must accept DoubleParametersArray.");
        }

        double summ = 0;
        vector<double> values = parametrs->get_values();
        for(size_t i=0; i<values.size(); i++)
        {
            double value = values[i];
            summ += 1/fabs(value*value - 2);
        }
        return summ; 
    }
};

void printStatistics(k52::optimization::GenerationStatistics s)
{
    cout << s.get_number_of_generation()<<" : "
                    << "Average fithess " << s.get_average_fitness() << " "
                    << ", Cache hits " << s.get_cache_hits() << " "
                    << ", Chromosome exceptions "<< s.get_invalid_chromosomes() << " "
                    << ", Currently best fitness "<< s.get_best_fitness() << " ";

    const DoubleParametersArray* bestParameters  =(const DoubleParametersArray*) s.get_best_parameters();

    cout.precision(15);
    cout<<"Values: ";

    vector<double> values = bestParameters->get_values();
    for(size_t i=0; i<values.size(); i++)
    {
        cout << values[i] << " ";
    }

    s.SaveCurrentPopulationToFile("Population.txt");

    cout << endl;
    int printFirst = 10;
    int i = 0;
    list<k52::optimization::IndividualStatistics> allIndividulasStatistics = s.get_all_individuals_statistics();
    for(list<k52::optimization::IndividualStatistics>::iterator it = allIndividulasStatistics.begin();
                    ( it != allIndividulasStatistics.end() ) && ( i<= printFirst ) ;
                    it++ , i++)
    {
        std::cout << " Ind-> fit:" << (*it).fitness <<
                        ", chosen: " << (*it).times_chosen_for_crossover <<std::endl;
    }

    cout << endl;
}

int main(int argc, char* argv[])
{
    time_t begin, end;
    time(&begin);
    cout << "Begin" << endl;

    int populationSize = 1000;
    int numberOfIterations = 10;
    int elitismPairs = 25;
    double mutation = 0.000001;
    double cacheLimitInMegabytes = 1;

    /////////////Genetic Algrythm///////////////
    k52::optimization::DoubleParametersArray parameters(GlobalMinValue, GlobalMaxValue, GlobalPrecision, GlobalNumberOfParameters);
    ExactDiscreteObjectiveFunction of;

    //TODO currently have to manually all nesessary objects
#ifdef BUILD_WITH_MPI
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( parameters );
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( of );
#endif

    cout<<"pr="<<GlobalPrecision<<"    apr="<<parameters.get_actual_precision()<<endl;

    k52::optimization::GeneticAlgorithm::shared_ptr ga =
        k52::optimization::GeneticAlgorithm::Create(populationSize, elitismPairs, numberOfIterations, cacheLimitInMegabytes, std::numeric_limits<double>::max(), mutation/*, "Population.txt"*/);

    //TODO FIX
    ga->OnNextGenerationReadyConnect(&printStatistics);

    try
    {
        ga->Optimize(of, &parameters, true);
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        return -1;
    }

    vector<double> values = parameters.get_values();

    for(size_t i=0; i<values.size(); i++)
    {
        cout<<i<<"-th parametr = "<<values[i]<<endl;
    }

    cout<<"Fitness = "<<of(&parameters)<<endl;
    /////////////Genetic Algrythm end///////////////

    time(&end);
    cout << "Time elapsed: " << difftime(end, begin) << " seconds "<< endl;
    return 0;
}
