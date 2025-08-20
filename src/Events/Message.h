#pragma once


using MessageType = unsigned int;

struct TwoFloats
{
	float X, Y;
};

struct Message
{
	Message(MessageType type) : MType(type) {}

	MessageType MType;
	int Sender;
	int Receiver;

	union 
	{
		TwoFloats Floats2;
		bool Boolean;
		int Integer;
	};
};