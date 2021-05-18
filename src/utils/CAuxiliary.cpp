#include <iostream>
#include "CAuxiliary.h"

CAuxiliary *CAuxiliary::m_instance = nullptr;

CAuxiliary *CAuxiliary::GetInstance()
{
	if (m_instance == 0)
	{
		m_instance = new CAuxiliary();
	}

	return m_instance;
}

CAuxiliary::CAuxiliary()
{
}

const void CAuxiliary::GetDirection(const CLocation *currLocation, const CLocation *destLocation, Cdirection *direction)
{
	auto directionX = destLocation->X() - currLocation->X();
	auto directionY = destLocation->Y() - currLocation->Y();

	if (directionX == 0 or directionY == 0)
	{
		direction->x = 0;
		direction->y = 0;
	}

	auto directionMagnitude = sqrtf(powf(directionX, 2) + powf(directionY, 2));
	auto directionUnitX = directionX / directionMagnitude;
	auto directionUnitY = directionY / directionMagnitude;

	/** @brief Because we are talking in pixel terms, we need to round things */
	if (directionUnitX >= 0)
		direction->x = (directionUnitX > 0.5) ? 1 : 0;
	else
		direction->x = (directionUnitX < -0.5) ? -1 : 0;

	if (directionUnitY >= 0)
		direction->y = (directionUnitY > 0.5) ? 1 : 0;
	else
		direction->y = (directionUnitY < -0.5) ? -1 : 0;
}

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
void CAuxiliary::MoveUnit(CLocation *currLocation, CLocation *destLocation, int directionOnX, int directionOnY, int speed, int boundaries)
{
	while (directionOnY != 0 && (currLocation->Y() != destLocation->Y()) && speed > 0)
	{
		currLocation->SetY(currLocation->Y() + directionOnY);
		--speed;
	}

	while (directionOnX != 0 && (currLocation->X() != destLocation->X()) && speed > 0)
	{
		currLocation->SetX(currLocation->X() + directionOnX);
		--speed;
	}

	if (speed > 0)
	{
		if (rand() % 100 < 50)
		{
			currLocation->SetX((currLocation->X() + speed * (rand() % 100)) % (boundaries - 1));
		}
		else
		{
			currLocation->SetY((currLocation->Y() + speed * (rand() % 100)) % (boundaries - 1));
		}
	}
}
