#include "EntityManager.h"

#include "PositionComponent.h"


EntityManager::EntityManager(SystemManager* systemManager, const std::shared_ptr<TextureManager>& textureManager) 
	: m_SystemManager(systemManager), m_TextureManager(textureManager)
{
	AddComponentType<PositionComponent>(Component::Position);
	//AddComponentType<SpriteSheetComponent>(Component::SpriteSheet);
	//AddComponentType<StateComponent>(Component::State);
	//AddComponentType<MovementComponent>(Component::Movement);
	//AddComponentType<ControllerComponent>(Component::Controller);
	//AddComponentType<ColliderComponent>(Component::Collider);
}

EntityManager::~EntityManager()
{
	Purge();
}

int EntityManager::AddEntity(Bitmask mask)
{
	unsigned int entityId = m_IdCounter;
	if (!m_Entities.emplace(entityId, EntityData(0, ComponentContainer())).second)
	{
		return -1;
	}

	++m_IdCounter;
	for (unsigned int i = 0; i < MAX_COMPONENT_TYPES; ++i)
	{
		if (mask.GetBit(i))
		{
			AddComponent(entityId, static_cast<Component>(i));
		}
	}

	//m_SystemManager->EntityModified(entityId, mask);
	//m_SystemManager->AddEvent(entityId, static_cast<EventID>(EntityEvent::Spawned);

	return entityId;
}

int EntityManager::AddEntity(const std::string& entityFile)
{
	return -1;
}

bool EntityManager::RemoveEntity(EntityId entityId)
{
	auto iter = m_Entities.find(entityId);
	if (iter == m_Entities.end())
	{
		return false;
	}

	auto& [entityID, entityData] = *iter;
	auto& [bitmask, componentContainer] = entityData;

	// clearing entity's components
	while (componentContainer.begin() != componentContainer.end())
	{
		delete componentContainer.back();
		componentContainer.pop_back();
	}

	m_Entities.erase(iter);
	//m_SystemManager->RemoveEntity(entityId);

	return true;
}

bool EntityManager::AddComponent(EntityId entityId, Component component)
{
	return true;
}

bool EntityManager::RemoveComponent(EntityId entityId, Component component)
{
	return true;
}

bool EntityManager::HasComponent(EntityId entityId, Component component)
{
	return true;
}

void EntityManager::Purge()
{

}

