#include "cache.h"

#include <stdexcept>
#include <iostream>

namespace k52
{
namespace optimization
{

Cache::shared_ptr Cache::Create(double data_limit_in_megabytes)
{
    return Cache::shared_ptr(new Cache(data_limit_in_megabytes));
}

bool Cache::IsCached(size_t parameters_hash)
{
    StoredValue stored_fitness = cache_map_[parameters_hash];
    return stored_fitness.has_value();
}

double Cache::GetCachedValue(size_t parameters_hash)
{
    StoredValue& stored_fitness = cache_map_[parameters_hash];
    if (stored_fitness.has_value())
    {
        stored_fitness.IncrementUsage();
        return stored_fitness.get_value();
    }
    else
    {
        throw std::runtime_error("Attempt to get uncached value");
    }
}

void Cache::AddValues(const std::vector<CacheRecord>& value_records)
{
    //Clear before adding to not remove new values
    ClearCacheUpToLimit();

    for (std::vector<CacheRecord>::const_iterator it = value_records.begin();
        it != value_records.end();
        ++it)
    {
        cache_map_[it->key] = StoredValue(it->value);
    }
}

void Cache::ClearCacheUpToLimit()
{
    //TODO improve cache clear algorithm
    if (IsSizeLimitExceeded())
    {
        int number_of_min_usage = 1;
        ClearUnusedCacheValues(number_of_min_usage);
    }

    if (IsSizeLimitExceeded())
    {
        throw std::runtime_error("Unable to clear cache up to limit");
    }
}

bool Cache::IsSizeLimitExceeded()
{
    double data_size_in_bytes = (sizeof(Cache::cache_map_type::key_type) + sizeof(Cache::cache_map_type::value_type)) * cache_map_.size();
    return (data_size_in_bytes / 1048576) > data_limit_in_megabytes_;
}

void Cache::ClearUnusedCacheValues(int number_of_min_usage)
{
    std::cout <<
        "Running ClearUnusedCacheValues. "
        "If this message appears many times consider improving the performance."
        << std::endl;

    Cache::cache_map_type::iterator it = cache_map_.begin();
    while (it != cache_map_.end())
    {
        if ((*it).second.get_number_of_usage() < number_of_min_usage)
        {
            cache_map_.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

Cache::Cache(double data_limit_in_megabytes)
{
    data_limit_in_megabytes_ = data_limit_in_megabytes;
}

}/* namespace optimization */
}/* namespace k52 */
