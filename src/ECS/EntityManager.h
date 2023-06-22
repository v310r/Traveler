#pragma once

#include "ResourceManagement/TextureManager.h"
#include "Utilities/Bitmask.h"
#include "BaseComponent.h"
#include <functional>


using EntityId = unsigned int;

using ComponentContainer = std::vector<BaseComponent*>;
using EntityData = std::pair<Bitmask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;
using ComponentFactory = std::unordered_map<Component, std::function<BaseComponent*(void)>>;


class SystemManager;

class EntityManager : std::enable_shared_from_this<EntityManager>
{
public:
	EntityManager(SystemManager* systemManager, const std::shared_ptr<TextureManager>& textureManager);

	~EntityManager();

	int AddEntity(Bitmask mask);
	int AddEntity(const std::string& entityFile);

	bool RemoveEntity(EntityId entityId);

	bool AddComponent(EntityId entityId, Component component);

	template<typename T>
	T* GetComponent(EntityId entityId, Component component)
	{
		auto iter = m_Entities.find(entityId);
		if (iter == m_Entities.end())
		{
			return nullptr;
		}

		auto& [entityId, entityData] = *iter;
		auto& [bitmask, componentContainer] = entityData;

		if (!bitmask.GetBit(static_cast<unsigned int>(component)))
		{
			// no such component
			return nullptr;
		}

		auto comp = std::find_if(componentContainer.begin(), componentContainer.end(), [component](BaseComponent* c)
		{
			return c->GetType() == component;
		});

		return (comp != componentContainer.end() ? dynamic_cast<T*>(*component) : nullptr);
	}

	bool RemoveComponent(EntityId entityId, Component component);

	bool HasComponent(EntityId entityId, Component component);

	void Purge();
private:
	template<typename T>
	void AddComponentType(Component component)
	{
		m_ComponentFactory[component] = []() -> BaseComponent*
		{
			return new T();
		};
	}

	unsigned int m_IdCounter = 0;
	EntityContainer m_Entities;
	ComponentFactory m_ComponentFactory;

	SystemManager* m_SystemManager;
	std::shared_ptr<TextureManager> m_TextureManager;
};