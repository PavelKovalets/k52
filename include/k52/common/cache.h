#ifndef CACHE_H_
#define CACHE_H_

#include <vector>
#include <stdexcept>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/common/stored_value.h>

namespace k52
{
namespace common
{

template <typename TKey, typename TValue>
class Cache
{
public:
    struct CacheRecord
    {
        CacheRecord(TKey key, TValue value)
            : key(key), value(value)
        {}

        TKey key;
        TValue value;
    };

    typedef boost::shared_ptr< Cache > shared_ptr;
    typedef boost::unordered_map< TKey, StoredValue< TValue > > cache_map_type;

    static typename Cache::shared_ptr Create(double data_limit_in_megabytes);

    bool IsCached(const TKey& key);

    TValue GetCachedValue(const TKey& key);

    void AddValue(const TKey& key, const TValue& value);

    void AddValues(const std::vector<CacheRecord>& value_records);

protected:
    void ClearCacheUpToLimit();
    bool IsSizeLimitExceeded();
    void ClearUnusedCacheValues(int number_of_min_usage);

private:
    Cache(double data_limit_in_megabytes);

    typename Cache::cache_map_type cache_map_;
    double data_limit_in_megabytes_;

    //DISALLOW_COPY_AND_ASSIGN
    Cache<TKey, TValue>(const Cache<TKey, TValue>&);
    void operator=(const Cache<TKey, TValue>&);
};

template <typename TKey, typename TValue>
typename Cache<TKey, TValue>::shared_ptr Cache<TKey, TValue>::Create(double data_limit_in_megabytes)
{
    if (data_limit_in_megabytes > 0)
    {
        return Cache<TKey, TValue>::shared_ptr(new Cache(data_limit_in_megabytes));
    }
    else
    {
        return Cache<TKey, TValue>::shared_ptr();
    }
}

template <typename TKey, typename TValue>
bool Cache<TKey, TValue>::IsCached(const TKey& key)
{
    StoredValue<TValue> stored_value = cache_map_[key];
    return stored_value.has_value();
}

template <typename TKey, typename TValue>
TValue Cache<TKey, TValue>::GetCachedValue(const TKey& key)
{
    StoredValue<TValue>& stored_value = cache_map_[key];
    if (stored_value.has_value())
    {
        stored_value.IncrementUsage();
        return stored_value.get_value();
    }
    else
    {
        throw std::runtime_error("Attempt to get uncached value");
    }
}

template <typename TKey, typename TValue>
void Cache<TKey, TValue>::AddValue(const TKey& key, const TValue& value)
{
    //Clear before adding to not remove new value
    ClearCacheUpToLimit();

    cache_map_[key] = StoredValue<TValue>(value);
}

template <typename TKey, typename TValue>
void Cache<TKey, TValue>::AddValues(const std::vector<CacheRecord>& value_records)
{
    //Clear before adding to not remove new values
    ClearCacheUpToLimit();

    for (typename std::vector<CacheRecord>::const_iterator it = value_records.begin();
         it != value_records.end();
         ++it)
    {
        cache_map_[it->key] = StoredValue<TValue>(it->value);
    }
}

template <typename TKey, typename TValue>
void Cache<TKey, TValue>::ClearCacheUpToLimit()
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

template <typename TKey, typename TValue>
bool Cache<TKey, TValue>::IsSizeLimitExceeded()
{
    double data_size_in_bytes =
            (
                    sizeof(typename Cache<TKey, TValue>::cache_map_type::key_type) +
                    sizeof(typename Cache<TKey, TValue>::cache_map_type::value_type)
            ) * cache_map_.size();
    return (data_size_in_bytes / 1048576) > data_limit_in_megabytes_;
}

template <typename TKey, typename TValue>
void Cache<TKey, TValue>::ClearUnusedCacheValues(int number_of_min_usage)
{
    std::cout <<
    "Running ClearUnusedCacheValues. "
            "If this message appears many times consider improving the performance."
    << std::endl;

    typename Cache<TKey, TValue>::cache_map_type::iterator it = cache_map_.begin();
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

template <typename TKey, typename TValue>
Cache<TKey, TValue>::Cache(double data_limit_in_megabytes)
{
    data_limit_in_megabytes_ = data_limit_in_megabytes;
}

}/* namespace common */
}/* namespace k52 */

#endif /* CACHE_H_ */
