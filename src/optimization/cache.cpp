#include "cache.h"

#include <stdexcept>

namespace k52
{
namespace optimization
{

Cache::shared_ptr Cache::Create()
{
    return Cache::shared_ptr(new Cache());
}

bool Cache::IsCached(size_t parameters_hash)
{
    StoredValue stored_fitness = cache_map_[parameters_hash];
    return stored_fitness.has_value();
}

double Cache::GetCachedValue(size_t parameters_hash)
{
    StoredValue stored_fitness = cache_map_[parameters_hash];
    if (stored_fitness.has_value())
    {
        return stored_fitness.get_value();
    }
    else
    {
        throw std::runtime_error("Attempt to get uncached value");
    }
}

void Cache::AddValue(size_t parameters_hash, double value)
{
    cache_map_[parameters_hash] = StoredValue(value);
}

}/* namespace optimization */
}/* namespace k52 */
