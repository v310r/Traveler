#pragma once

#include <queue>


using EventId = unsigned int;

class EventQueue
{
public:
	void AddEvent(EventId eventId) { m_Queue.push(eventId); }

	bool ProcessEvents(EventId& eventId);

	void Clear();

private:
	std::queue<EventId> m_Queue;
};

