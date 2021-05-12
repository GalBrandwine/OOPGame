#pragma once
class CUnitProperty
{
public:
	CUnitProperty(int speed, int range, int probability);

	int GetSpeed()
	{
		return Speed;
	}

	int GetHitRange()
	{
		return m_hitRange;
	}

	int GetProbability()
	{
		return m_hitProbability;
	}

private:
	int Speed = 0;
	int m_hitRange = 0;
	int m_hitProbability = 0;
};

