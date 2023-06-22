#pragma once

#include "TypesECS.h"
#include <sstream>


class BaseComponent
{
public:
	BaseComponent(Component type) : m_Type(type) {}

	virtual ~BaseComponent() {}

	virtual void ReadIn(std::stringstream& stream) = 0;

	Component GetType() { return m_Type; }

	friend std::stringstream& operator>>(std::stringstream& stream, BaseComponent& component)
	{
		component.ReadIn(stream);
		return stream;
	}

protected:
	Component m_Type;
};