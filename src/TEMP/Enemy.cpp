#include "Enemy.h"

#include <cstdlib>
#include "Animation/SpriteSheet.h"
#include "Animation/AnimBase.h"


Enemy::Enemy(const std::shared_ptr<EntityManagerOld>& entityManager) : Character(entityManager)
{
	m_Type = EEntityType::Enemy;
}

Enemy::~Enemy()
{

}

void Enemy::OnEntityCollision(EntityBase* collidedEntity, bool bAttack)
{
	if (m_State == EEntityState::Dying || !bAttack || collidedEntity->GetType() != EEntityType::Player)
	{
		return;
	}

	if (!m_SpriteSheet->GetCurrentAnimation()->IsInAction())
	{
		return;
	}

	Character* player = static_cast<Character*>(collidedEntity);
	SetState(EEntityState::Attacking);
	player->GetHurt(1);

	if (m_Position.x > player->GetPosition().x)
	{
		player->AddVelocity(-m_Speed.x, 0.0f);
		m_SpriteSheet->SetDirection(SpriteDirection::Left);
	}
	else
	{
		player->AddVelocity(m_Speed.x, 0.0f);
		m_SpriteSheet->SetDirection(SpriteDirection::Right);
	}
}

void Enemy::Update(float deltaTime)
{
	Character::Update(deltaTime);

	if (m_bHasDestination)
	{
		if (std::abs(m_Destination.x - m_Position.x) < 16.0f)
		{
			m_bHasDestination = false;
			return;
		}

		if (m_Destination.x - m_Position.x > 0)
		{
			Move(SpriteDirection::Right);
		}
		else
		{
			Move(SpriteDirection::Left);
		}

		if (m_bCollidingOnX)
		{
			m_bHasDestination = false;
		}

		return;
	}

	const int randomValue = std::rand() % 1000 + 1;
	if (randomValue != 1000)
	{
		return;
	}

	int newX = std::rand() % 65;
	if (std::rand() % 2)
	{
		newX = -newX;
	}

	m_Destination.x = m_Position.x + newX;
	if (m_Destination.x < 0.0f)
	{
		m_Destination.x = 0.0f;
	}

	m_bHasDestination = true;
}
