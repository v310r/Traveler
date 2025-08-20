#include "EventQueue.h"


bool EventQueue::ProcessEvents(EventId& eventId)
{
	if (m_Queue.empty())
	{
		return false;
	}

	eventId = m_Queue.front();
	m_Queue.pop();
	return true;
}

void EventQueue::Clear()
{
	while (!m_Queue.empty())
	{
		m_Queue.pop();
	}
}
