#pragma once

#include <cstdint>


using Bitset = uint32_t;

class Bitmask
{
public:
	Bitmask() : m_Bits(0) {}

	Bitmask(Bitset bits) : m_Bits(bits) {}

	Bitset GetMask()const { return m_Bits; }
	void SetMask(Bitset value) { m_Bits = value; }

	bool Matches(Bitmask bits, Bitset relevant = 0) const
	{
		return (relevant ? ((bits.GetMask() & relevant) == (m_Bits & relevant)) : (bits.GetMask() == m_Bits));
	}

	bool GetBit(unsigned int pos) const
	{
		return ((m_Bits & (1 << pos)) != 0);
	}

	void TurnOnBit(unsigned int pos)
	{
		m_Bits |= 1 << pos;
	}

	void TurnOnBits(unsigned int pos)
	{
		m_Bits |= pos;
	}

	void ClearBit(unsigned int pos)
	{
		m_Bits &= ~(1 << pos);
	}

	void ToggleBit(unsigned int pos)
	{
		m_Bits ^= 1 << pos;
	}

	void Clear() { m_Bits = 0; }


private:
	Bitset m_Bits;
};
