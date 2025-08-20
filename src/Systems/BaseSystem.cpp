#include "BaseSystem.h"

#include "SystemManager.h"


BaseSystem::BaseSystem(SystemId id, const std::shared_ptr<SystemManager> systemManager)
	: m_Id(id), m_SystemManager(systemManager)
{

}

BaseSystem::~BaseSystem()
{
	Purge();
}

bool BaseSystem::AddEntity(EntityId entityId)
{
	if (HasEntity(entityId))
	{
		return false;
	}

	m_Entities.emplace_back(entityId);
	return true;
}

bool BaseSystem::HasEntity(EntityId entityId)
{
	return std::find(m_Entities.begin(), m_Entities.end(), entityId) != m_Entities.end();
}

bool BaseSystem::RemoveEntity(EntityId entityId)
{
	auto entity = std::find_if(m_Entities.begin(), m_Entities.end(), [entityId](EntityId id)
	{
		return id == entityId;
	});

	if (entity == m_Entities.end())
	{
		return false;
	}

	return true;
}

SystemId BaseSystem::GetId()
{
	return 0;
}

bool BaseSystem::FitsRequirements(Bitmask bits) const
{
	return std::find_if(m_RequiredComponents.begin(), m_RequiredComponents.end(), [bits](Bitmask bm) { return bm.Matches(bits, bm.GetMask()); }) != m_RequiredComponents.end();
}

void BaseSystem::Purge()
{
	m_Entities.clear();
}
