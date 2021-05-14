#pragma once
#include "CLocation.h"

/**
 * @brief Im not sure what this CAuxiliary creature is.
 * * *It looks like a singeltone, that acts like a factory. But why?*
 * 
 */
class CAuxiliary
{
public:
	static CAuxiliary* GetInstance();

	static int TryHitOpponent(int probability);
	static void MoveUnit(CLocation* currLocation, CLocation* destLocation, int directionOnX, int directionOnY, int speed);

private:
	CAuxiliary();
	static CAuxiliary* m_instance;
};

