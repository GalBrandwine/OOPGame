#include <iostream>
#include "CAuxiliary.h"

CAuxiliary* CAuxiliary::m_instance = nullptr;

CAuxiliary* CAuxiliary::GetInstance()
{
    if (m_instance == 0)
    {
        m_instance = new CAuxiliary();
    }

    return m_instance;
}

CAuxiliary::CAuxiliary()
{ }

/*
* Calculates attack / defend success according to the unit probability.
*/
int CAuxiliary::TryHitOpponent(int probability)
{
	if (rand() % 100 < probability)
	{
		return 1;
	}

	return 0;
}

/**
* Updates unit current location.
*/
void CAuxiliary::MoveUnit(CLocation* currLocation, CLocation* destLocation, int directionOnX, int directionOnY, int speed)
{
	while ((currLocation->Y() != destLocation->Y()) && speed > 0)
	{
		currLocation->SetY(currLocation->Y() + directionOnY);
		--speed;
	}

	while ((currLocation->X() != destLocation->X()) && speed > 0)
	{
		currLocation->SetX(currLocation->X() + directionOnX);
		--speed;
	}

	if (speed > 0)
	{
		if (rand() % 100 < 50)
		{
			currLocation->SetX(currLocation->X() + speed * directionOnX);
		}
		else
		{
			currLocation->SetY(currLocation->Y() + speed * directionOnY);
		}
	}
}

