#pragma once

#include "Events/MessageHandler.h"
#include "BaseSystem.h"
#include "Events/EventQueue.h"
#include "Window/Window.h"
#include "Utilities/TypesECS.h"


using SystemContainer = std::unordered_map<ESystem, BaseSystem*>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;

class EntityManager;

class SystemManager
{
public:
	SystemManager();

	~SystemManager();

	void SetEntityManager(std::shared_ptr<EntityManager> entityManager);
	std::shared_ptr<EntityManager> GetEntityManager();
	MessageHandler& GetMessageHandler();

	template<typename T>
	T* GetSystem(ESystem system) const
	{
		auto iter = m_Systems.find(system);
		return iter != m_Systems.end() ? dynamic_cast<T*>(iter->second) : nullptr;
	}

	void AddEvent(EntityId entityId, EventId eventId);

	void Update(float deltatTime);
	void HandleEvents();
	void Draw(Window* window, unsigned int elevation);

	void EntityModified(EntityId entityId, Bitmask bitmask);
	void RemoveEntity(EntityId entityId);

	void PurgeEntities();
	void PurgeSystems();
private:
	SystemContainer m_Systems;
	std::weak_ptr<EntityManager> m_EntityManager;
	EntityEventContainer m_Events;
	MessageHandler m_Messages;
};

