#pragma once

#include "Message.h"
#include <vector>
#include <algorithm>


class Observer
{
public:
	virtual ~Observer() {}

	virtual void Notify(const Message& message) = 0;
};


using ObserverContainer = std::vector<Observer*>;


class Communicator
{
public:
	~Communicator() { m_Observers.clear(); }

	bool AddObserver(Observer* observer)
	{
		if (HasObserver(observer))
		{
			return false;
		}

		m_Observers.emplace_back(observer);
		return true;
	}

	bool RemoveObserver(Observer* observer)
	{
		auto iter = std::find_if(m_Observers.begin(), m_Observers.end(), [observer](Observer* o)
		{
			return o == observer;
		});

		if (iter == m_Observers.end())
		{
			return false;
		}

		m_Observers.erase(iter);
		return true;
	}

	bool HasObserver(const Observer* const observer) const
	{
		return std::find_if(m_Observers.begin(), m_Observers.end(), [observer](Observer* o)
		{
			return o == observer;
		}) != m_Observers.end();
	}

	void Broadcast(const Message& message)
	{
		for (Observer* observer : m_Observers)
		{
			observer->Notify(message);
		}
	}

private:
	ObserverContainer m_Observers;
};