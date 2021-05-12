#pragma once
#include "CLocation.h"

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

