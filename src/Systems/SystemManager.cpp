#include "SystemManager.h"


SystemManager::SystemManager()
{
    //m_Systems[ESystem::State] = new StateSystem(this);
    //m_Systems[ESystem::Control] = new ControlSystem(this);
    //m_Systems[ESystem::Movement] = new MovementSystem(this);
    //m_Systems[ESystem::Collision] = new CollisionSystem(this);
    //m_Systems[ESystem::SheetAnimation] = new SheetAnimationSystem(this);
    //m_Systems[ESystem::Renderer] = new RendererSystem(this);

}

SystemManager::~SystemManager()
{
    PurgeSystems();
}

void SystemManager::SetEntityManager(std::shared_ptr<EntityManager> entityManager)
{

}

std::shared_ptr<EntityManager> SystemManager::GetEntityManager()
{
    return nullptr;
}

MessageHandler& SystemManager::GetMessageHandler()
{
    return MessageHandler();
}

void SystemManager::AddEvent(EntityId entityId, EventId eventId)
{

}

void SystemManager::Update(float deltatTime)
{

}

void SystemManager::HandleEvents()
{

}

void SystemManager::Draw(Window* window, unsigned int elevation)
{

}

void SystemManager::EntityModified(EntityId entityId, Bitmask bitmask)
{

}

void SystemManager::RemoveEntity(EntityId entityId)
{

}

void SystemManager::PurgeEntities()
{

}

void SystemManager::PurgeSystems()
{

}
