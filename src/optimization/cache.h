#ifndef CACHE_H_
#define CACHE_H_

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
    typedef boost::shared_ptr<Cache> shared_ptr;

    static Cache::shared_ptr Create();

    bool IsCached(size_t parameters_hash);

    double GetCachedValue(size_t parameters_hash);

    void AddValue(size_t parameters_hash, double value);

private:
    Cache() {}

    boost::unordered_map<std::size_t, StoredValue> cache_map_;

    DISALLOW_COPY_AND_ASSIGN(Cache);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CACHE_H_ */
