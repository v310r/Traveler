#pragma once


using EntityId = unsigned int;


enum class EEntityType
{
	Base,
	Enemy,
	Player
};

enum class EEntityState
{
	Idle,
	Walking,
	Jumping,
	Attacking,
	Hurt,
	Dying
};

enum class EEntityEvent
{
	Spawned,
	Despawned,
	CollidingX,
	CollidingY,
	MovingLeft,
	MovingRight,
	MovingUp,
	MovingDown,
	ElevationChange,
	BecameIdle,
	BeganMoving
};

enum class EEntityMessage
{
	Move, 
	IsMoving,
	StateChanged,
	DirectionChanged,
	SwitchState,
	AttackAction,
	Dead
};