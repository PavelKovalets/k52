#include <k52/parallel/mpi/identifyable_objects_manager.h>

#include <stdexcept>
#include <string>
#include <sstream>
#include <typeinfo>

namespace k52
{
namespace parallel
{
namespace mpi
{

using ::k52::common::ICloneable;

IdentifyableObjectsManager::IdentifyableObjectsManager() {}

const ICloneable* IdentifyableObjectsManager::GetObject(const std::string& id)
{
    ICloneable::shared_ptr corresponding_object = registered_objects_[id];
    if(corresponding_object == NULL)
    {
        std::stringstream message;
        message << "Object with id " << id << " was not registered. "
            "Try to call IdentifyableObjectsManager::Instance().registerObject "
            "passing an instance of unregistered class as a parameter "
            "before system (e.g. MPI) initialization.";

        throw std::invalid_argument(message.str());
    }

    return corresponding_object.get();
}

void IdentifyableObjectsManager::RegisterObject(const ICloneable& object)
{
    registered_objects_[IdentifyableObjectsManager::GetId(object)] = ICloneable::shared_ptr( object.Clone() );
}

std::string IdentifyableObjectsManager::GetId(const ICloneable& object)
{
    return typeid(object).name();
}

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */


