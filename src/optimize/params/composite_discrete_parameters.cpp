#include <optimize/params/composite_discrete_parameters.h>

#include <stdexcept>

namespace k52
{
namespace optimize
{

CompositeDiscreteParameters* CompositeDiscreteParameters::Clone() const
{
    initialization_checker_.InitializationCheck();

    CompositeDiscreteParameters* clone = new CompositeDiscreteParameters();
    clone->Initialize(parameters_set_);
    return clone;
}

bool CompositeDiscreteParameters::CheckConstraints() const
{
    initialization_checker_.InitializationCheck();

    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        if(!parameters_set_[i]->CheckConstraints())
        {
            return false;
        }
    }
    return true;
}

void CompositeDiscreteParameters::SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
    initialization_checker_.InitializationCheck();

    size_t chromosome_size = to - from;

    this->CheckForConstChromosomeSize(chromosome_size);

    std::vector<bool>::iterator current_from = from;

    for(size_t i = 0; i < parameters_set_.size(); i++)
    {
        size_t parameter_chromosome_size = parameters_set_[i]->GetChromosomeSize();

        std::vector<bool>::iterator current_to = current_from + parameter_chromosome_size;

        parameters_set_[i]->SetChromosome(current_from, current_to);

        current_from = current_to;
    }
}

void CompositeDiscreteParameters::SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to)
{
    initialization_checker_.InitializationCheck();

    size_t chromosome_size = to - from;

    this->CheckForConstChromosomeSize(chromosome_size);

    std::vector<bool>::const_iterator current_from = from;

    for(size_t i = 0; i < parameters_set_.size(); i++)
    {
        size_t parameter_chromosome_size = parameters_set_[i]->GetChromosomeSize();

        std::vector<bool>::const_iterator current_to = current_from + parameter_chromosome_size;

        parameters_set_[i]->SetFromChromosome(current_from, current_to);

        current_from = current_to;
    }
}

void CompositeDiscreteParameters::Initialize(std::vector<IDiscreteParameters::shared_ptr> parameters)
{
    parameters_set_ = std::vector<IDiscreteParameters::shared_ptr>(parameters.size());

    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        parameters_set_[i] = IDiscreteParameters::shared_ptr(parameters[i]->Clone());
    }

    this->SetConstChromosomeSize( CountTotalChromosomeSize() );

    initialization_checker_.SetInitialized();
}

size_t CompositeDiscreteParameters::GetNumberOfParameters() const
{
    initialization_checker_.InitializationCheck();

    return parameters_set_.size();
}

const IDiscreteParameters::shared_ptr CompositeDiscreteParameters::GetParameter(size_t index) const
{
    initialization_checker_.InitializationCheck();

    if(index+1 > parameters_set_.size())
    {
        throw std::out_of_range("index in getParameter method is out of range");
    }

    return parameters_set_[index];
}

size_t CompositeDiscreteParameters::CountTotalChromosomeSize() const
{
    size_t total_chromosome_size = 0;
    for(size_t i=0; i<parameters_set_.size(); i++)
    {
        total_chromosome_size += parameters_set_[i]->GetChromosomeSize();
    }
    return total_chromosome_size;
}

}/* namespace optimize */
}/* namespace k52 */

