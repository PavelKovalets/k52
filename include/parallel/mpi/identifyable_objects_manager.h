#ifndef IDENTIFYABLEOBJECTSMANAGER_H_
#define IDENTIFYABLEOBJECTSMANAGER_H_

#include <map>
#include <string>

#include <common/disallow_copy_and_assign.h>
#include <common/i_cloneable.h>
#include <parallel/i_task.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class IdentifyableObjectsManager
{
public:
    const k52::common::ICloneable* GetObject(const std::string& id);

    void RegisterObject(const k52::common::ICloneable& object);

    static std::string GetId(const k52::common::ICloneable& object);

    static IdentifyableObjectsManager& Instance()
    {
        static IdentifyableObjectsManager self;
        return self;
    }

private:
    typedef std::map<std::string, k52::common::ICloneable::shared_ptr> IdentifyableObjectsContainer;

    IdentifyableObjectsManager();

    IdentifyableObjectsContainer registered_objects_;

    DISALLOW_COPY_AND_ASSIGN(IdentifyableObjectsManager);
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IDENTIFYABLEOBJECTSMANAGER_H_ */
