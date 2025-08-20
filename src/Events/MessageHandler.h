#pragma once

#include "Utilities/EntityHelper.h"
#include "Communicator.h"
#include <unordered_map>


using Subscriptions = std::unordered_map<EEntityMessage, Communicator>;


class MessageHandler
{
public:
	bool Subscribe(EEntityMessage entityMessage, Observer* observer)
	{
		return m_Communicators[entityMessage].AddObserver(observer);
	}

	bool Unsubscribe(EEntityMessage entityMessage, Observer* observer)
	{
		return m_Communicators[entityMessage].RemoveObserver(observer);
	}

	void Dispatch(const Message& message)
	{
		auto iter = m_Communicators.find(static_cast<EEntityMessage>(message.MType));
		if (iter == m_Communicators.end())
		{
			return;
		}

		auto& [entityMessage, communicator] = *iter;
		communicator.Broadcast(message);
	}

private:
	Subscriptions m_Communicators;
};