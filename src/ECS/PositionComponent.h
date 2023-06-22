#pragma once

#include "BaseComponent.h"
#include "SFML/System/Vector2.hpp"


class PositionComponent : public BaseComponent
{
public:
	PositionComponent();

	virtual ~PositionComponent();

	virtual void ReadIn(std::stringstream& stream) override;

	sf::Vector2f GetPosition() const { return m_Position; }
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f value);

	sf::Vector2f GetOldPosition() const { return m_OldPosition; }

	unsigned int GetElevation() const { return m_Elevation; }
	void SetElevation(unsigned int elevation) { m_Elevation = elevation; }

	void MoveBy(float x, float y);
	void MoveBy(sf::Vector2f value);

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_OldPosition;
	unsigned int m_Elevation;
};

