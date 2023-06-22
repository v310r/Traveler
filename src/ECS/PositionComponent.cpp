#include "PositionComponent.h"

PositionComponent::PositionComponent() : BaseComponent(Component::Position), m_Elevation(0)
{

}

PositionComponent::~PositionComponent()
{

}

void PositionComponent::ReadIn(std::stringstream& stream)
{
	stream >> m_Position.x >> m_Position.y >> m_Elevation;
}

void PositionComponent::SetPosition(float x, float y)
{
	m_OldPosition = m_Position;
	m_Position = sf::Vector2f(x, y);
}

void PositionComponent::SetPosition(sf::Vector2f value)
{
	m_OldPosition = m_Position;
	m_Position = value;
}

void PositionComponent::MoveBy(float x, float y)
{
	m_OldPosition = m_Position;
	m_Position += sf::Vector2f(x, y);
}

void PositionComponent::MoveBy(sf::Vector2f value)
{
	m_OldPosition = m_Position;
	m_Position += value;
}
