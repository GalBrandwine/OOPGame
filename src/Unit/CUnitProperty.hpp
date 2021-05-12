#pragma once
#include <iostream>

#define DEFAULT_SPEED 1

class CUnitProperty
{
protected:
    int Range;
    int Speed = DEFAULT_SPEED;
    int Probability;

public:
    /**
     * @brief Construct a new CUnitProperty object
     * 
     * @param speed the distance the unit can cover in one turn.
     * @param range the distance from which the unit can hit.
     * @param probability probability to hit the target.
     */
    CUnitProperty(int range, int probability, int speed);

    /**
     * @brief Overload constructor so Unit could be created without speed
     * 
     * @param range the distance from which the unit can hit.
     * @param probability probability to hit the target.
     */
    CUnitProperty(int range, int probability);

    ~CUnitProperty();
};
