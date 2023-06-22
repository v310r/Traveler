#pragma once

using ComponentType = unsigned int;
constexpr int MAX_COMPONENT_TYPES = 32;

enum class Component
{
	Position = 0,
	SpriteSheet,
	State,
	Movement,
	Controller,
	Collider
};

enum class System
{
	Renderer = 0,
	Motion,
	Collision,
	Control,
	State,
	SheetAnimation
};
