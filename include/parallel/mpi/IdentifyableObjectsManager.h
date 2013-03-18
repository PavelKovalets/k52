/*
 * TasksManager.h
 *
 *  Created on: Oct 14, 2012
 *      Author: pavel
 */

#ifndef IDENTIFYABLEOBJECTSMANAGER_H_
#define IDENTIFYABLEOBJECTSMANAGER_H_

#include <common/disallow_copy_and_assign.h>
#include <parallel/i_task.h>
#include <common/i_cloneable.h>
#include <map>
#include <string>

namespace k52
{
namespace parallel
{
namespace mpi
{
typedef std::map<std::string, k52::common::ICloneable*> IdentifyableObjectsContainer;

class IdentifyableObjectsManager
{
public:
	static IdentifyableObjectsManager& Instance()
	{
		static IdentifyableObjectsManager self;
		return self;
	}

	const k52::common::ICloneable* getObject(std::string id);

	void registerObject(k52::common::ICloneable* object);

	static std::string getId(const k52::common::ICloneable* object);

private:
	IdentifyableObjectsManager();
	~IdentifyableObjectsManager();

	IdentifyableObjectsContainer _registeredObjects;

	DISALLOW_COPY_AND_ASSIGN(IdentifyableObjectsManager);
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IDENTIFYABLEOBJECTSMANAGER_H_ */
