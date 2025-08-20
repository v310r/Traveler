#pragma once

using ComponentType = unsigned int;
constexpr int MAX_COMPONENT_TYPES = 32;

enum class EComponent
{
	Position = 0,
	SpriteSheet,
	State,
	Movement,
	Controller,
	Collider
};

enum class ESystem
{
	Renderer = 0,
	Movement,
	Collision,
	Control,
	State,
	SheetAnimation
};
