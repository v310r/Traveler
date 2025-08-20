#include "EntityManager.h"

#include "Components/PositionComponent.h"


EntityManager::EntityManager(SystemManager* systemManager, const std::shared_ptr<TextureManager>& textureManager) 
	: m_SystemManager(systemManager), m_TextureManager(textureManager)
{
	AddComponentType<PositionComponent>(EComponent::Position);
	//AddComponentType<SpriteSheetComponent>(EComponent::SpriteSheet);
	//AddComponentType<StateComponent>(EComponent::State);
	//AddComponentType<MovementComponent>(EComponent::Movement);
	//AddComponentType<ControllerComponent>(EComponent::Controller);
	//AddComponentType<ColliderComponent>(EComponent::Collider);
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
			AddComponent(entityId, static_cast<EComponent>(i));
		}
	}

	//m_SystemManager->EntityModified(entityId, mask);
	//m_SystemManager->AddEvent(entityId, static_cast<EventId>(EEntityEvent::Spawned);

	return entityId;
}

int EntityManager::AddEntity(const std::string& entityFile)
{
	int entityId = -1;
	std::ifstream file;
	file.open(std::filesystem::current_path() / entityFile);
	if (!file.is_open())
	{
		std::cerr << "Failed to load entity: " << entityFile << ", src: " << __FILE__ << std::endl;
		return -1;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '|')
		{
			continue;
		}

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Name")
		{

		}
		else if (type == "Attributes")
		{
			if (entityId != -1)
			{
				continue;
			}

			Bitset set = 0;
			Bitmask mask;

			keystream >> set;
			mask.SetMask(set);
			entityId = AddEntity(mask);
			if (entityId == -1)
			{
				return -1;
			}
		}
		else if (type == "Component")
		{
			if (entityId == -1)
			{
				continue;
			}

			unsigned int componentId = 0;
			keystream >> componentId;
			BaseComponent* component = GetComponent<BaseComponent>(entityId, static_cast<EComponent>(componentId));
			if (!component)
			{
				continue;
			}

			keystream >> *component;
			if (component->GetType() == EComponent::SpriteSheet)
			{
				//SpriteSheetComponent* sheet = static_cast<SpriteSheetComponent>(component);
				//sheet->Create(m_TextureManager);
			}
		}
	}

	return entityId;
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

bool EntityManager::AddComponent(EntityId entityId, EComponent component)
{
	auto iter = m_Entities.find(entityId);
	if (iter == m_Entities.end())
	{
		return false;
	}

	auto& [entityID, entityData] = *iter;
	auto& [bitmask, componentContainer] = entityData;
	if (bitmask.GetBit(static_cast<unsigned int>(component)))
	{
		// component already exist
		return false;
	}

	auto iter2 = m_ComponentFactory.find(component);
	if (iter2 == m_ComponentFactory.end())
	{
		return false;
	}

	auto& [componentType, callFactoryFunction] = *iter2;
	BaseComponent* componentObj = callFactoryFunction();
	componentContainer.emplace_back(componentObj);
	bitmask.TurnOnBit(static_cast<unsigned int>(component));

	//m_SystemManager->EntityModified(entityId, bitmask);

	return true;
}

bool EntityManager::RemoveComponent(EntityId entityId, EComponent component)
{
	auto iter = m_Entities.find(entityId);
	if (iter == m_Entities.end())
	{
		return false;
	}

	auto& [entityID, entityData] = *iter;
	auto& [bitmask, componentContainer] = entityData;
	if (!bitmask.GetBit(static_cast<unsigned int>(component)))
	{
		// no such component
		return false;
	}

	auto componentIter = std::find_if(componentContainer.begin(), componentContainer.end(),
	[&](BaseComponent* c)
	{
		return c->GetType() == component;
	});

	if (componentIter == componentContainer.end())
	{
		return false;
	}

	delete (*componentIter);
	componentContainer.erase(componentIter);
	bitmask.ClearBit(static_cast<unsigned int>(component));

	//m_SystemManager->EntityModified(entityId, bitmask);
	return true;
}

bool EntityManager::HasComponent(EntityId entityId, EComponent component)
{
	auto iter = m_Entities.find(entityId);
	if (iter == m_Entities.end())
	{
		return false;
	}

	return iter->second.first.GetBit(static_cast<unsigned int>(component));
}

void EntityManager::Purge()
{
	//m_SystemManager->PurgeEntities();
	for (auto& [entityId, entityData] : m_Entities)
	{
		auto& [bitmask, componentContainer] = entityData;
		for (auto& component : componentContainer)
		{
			delete component;
		}

		componentContainer.clear();
		bitmask.Clear();
	}

	m_Entities.clear();
	m_IdCounter = 0;
}

