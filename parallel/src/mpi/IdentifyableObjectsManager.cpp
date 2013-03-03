/*
 * TasksManager.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#include "../../include/mpi/IdentifyableObjectsManager.h"
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
			IdentifyableObjectsManager::IdentifyableObjectsManager() {}

			IdentifyableObjectsManager::~IdentifyableObjectsManager()
			{
				for(IdentifyableObjectsContainer::iterator it = _registeredObjects.begin();
						it!=_registeredObjects.end(); it++)
				{
					delete ( (*it).second );
				}
			}

			const k52::common::ICloneable* IdentifyableObjectsManager::getObject(std::string id)
			{
				k52::common::ICloneable* correspondingObject = _registeredObjects[id];
				if(correspondingObject == NULL)
				{
					std::stringstream message;
					message << "Object with id " << id << " was not registered. "
							"Try to call IdentifyableObjectsManager::Instance().registerObject "
							"passing an instance of unregistered class as a parameter "
							"before system (e.g. MPI) initialization.";

					throw std::invalid_argument(message.str());
				}

				return correspondingObject;
			}

			void IdentifyableObjectsManager::registerObject(k52::common::ICloneable* object)
			{
				_registeredObjects[IdentifyableObjectsManager::getId(object)] = object->clone();
			}

			std::string IdentifyableObjectsManager::getId(const k52::common::ICloneable* object)
			{
				return typeid(*object).name();
			}
		}
	}
}


