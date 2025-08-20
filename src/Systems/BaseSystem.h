#pragma once

#include "Events/Communicator.h"
#include "Utilities/EntityHelper.h"
#include "Utilities/Bitmask.h"
#include <vector>
#include <memory>


using SystemId = unsigned int;

using EntityList = std::vector<EntityId>;
using Requirements = std::vector<Bitmask>;

class SystemManager;

class BaseSystem : public Observer
{
public:
	BaseSystem(SystemId id, const std::shared_ptr<SystemManager> systemManager);

	virtual ~BaseSystem();

	virtual void Update(float deltaTime) = 0;

	virtual void HandleEvent(EntityId entityId, EEntityEvent entityEvent) = 0;

	bool AddEntity(EntityId entityId);
	bool HasEntity(EntityId entityId);
	bool RemoveEntity(EntityId entityId);

	SystemId GetId();

	bool FitsRequirements(Bitmask bits) const;
	
	void Purge();

protected:
	SystemId m_Id;
	Requirements m_RequiredComponents;
	EntityList m_Entities;

	std::weak_ptr<SystemManager> m_SystemManager;
};

