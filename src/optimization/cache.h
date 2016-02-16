#ifndef CACHE_H_
#define CACHE_H_

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <k52/common/disallow_copy_and_assign.h>

#include "stored_value.h"

namespace k52
{
namespace optimization
{

class Cache
{
public:
    struct CacheRecord
    {
        CacheRecord(size_t key, double value) 
            : key(key), value(value)
        {}

        size_t key;
        double value;
    };

    typedef boost::shared_ptr<Cache> shared_ptr;
    typedef boost::unordered_map<std::size_t, StoredValue> cache_map_type;

    static Cache::shared_ptr Create(double data_limit_in_megabytes);

    bool IsCached(size_t parameters_hash);

    double GetCachedValue(size_t parameters_hash);

    void AddValues(const std::vector<CacheRecord>& value_records);

protected:
    void ClearCacheUpToLimit();
    bool IsSizeLimitExceeded();
    void ClearUnusedCacheValues(int number_of_min_usage);

private:
    Cache(double data_limit_in_megabytes);

    Cache::cache_map_type cache_map_;
    double data_limit_in_megabytes_;

    DISALLOW_COPY_AND_ASSIGN(Cache);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CACHE_H_ */
