#pragma once

#include "Character.h"


class EntityManagerOld;


class Enemy : public Character
{
public:
	Enemy(const std::shared_ptr<EntityManagerOld>& entityManager);

	~Enemy();

	void OnEntityCollision(EntityBase* collidedEntity, bool bAttack) override;

	virtual void Update(float deltaTime) override;

private:
	sf::Vector2f m_Destination;

	bool m_bHasDestination = false;
};

