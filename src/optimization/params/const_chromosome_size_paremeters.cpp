#include <k52/optimization/params/const_chromosome_size_paremeters.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

ConstChromosomeSizeParemeters::ConstChromosomeSizeParemeters()
{
    was_chromosome_size_set_ = false;
    chromosome_size_ = 0;
}

size_t ConstChromosomeSizeParemeters::GetChromosomeSize() const
{
    CheckIfChromosomeWasSet();
    return chromosome_size_;
}

void ConstChromosomeSizeParemeters::SetConstChromosomeSize(size_t chromosome_size)
{
    if(was_chromosome_size_set_)
    {
        throw std::logic_error("ChromosomeSize must only be set once");
    }
    else
    {
        was_chromosome_size_set_ = true;
        chromosome_size_ = chromosome_size;
    }
}

void ConstChromosomeSizeParemeters::CheckForConstChromosomeSize(size_t chromosome_size) const
{
    CheckIfChromosomeWasSet();

    if(chromosome_size != chromosome_size_)
    {
        throw std::invalid_argument("Chromosome size do not match");
    }
}

void ConstChromosomeSizeParemeters::CheckIfChromosomeWasSet() const
{
    if(!was_chromosome_size_set_)
    {
        throw std::logic_error("Chromosome size was not set."
            " Please call SetConstChromosomeSize before using ConstChromosomeSizeParemeters");
    }
}

}/* namespace optimization */
}/* namespace k52 */
