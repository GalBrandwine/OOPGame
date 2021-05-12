#pragma once
class CUnitProperty
{
public:
	CUnitProperty(int speed, int range, int probability);

	int GetSpeed()
	{
		return m_speed;
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
	int m_speed = 0;
	int m_hitRange = 0;
	int m_hitProbability = 0;
};

