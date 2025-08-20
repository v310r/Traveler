#pragma once

#include "Utilities/TypesECS.h"
#include <sstream>


class BaseComponent
{
public:
	BaseComponent(EComponent type) : m_Type(type) {}

	virtual ~BaseComponent() {}

	virtual void ReadIn(std::stringstream& stream) = 0;

	EComponent GetType() { return m_Type; }

	friend std::stringstream& operator>>(std::stringstream& stream, BaseComponent& component)
	{
		component.ReadIn(stream);
		return stream;
	}

protected:
	EComponent m_Type;
};