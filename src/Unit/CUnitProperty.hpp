#pragma once
#include <iostream>

#define DEFAULT_SPEED 1
#define DEFAULT_LOCATION -1

class CUnitProperty
{
private:
    int m_hitRange;
    int m_speed = DEFAULT_SPEED;
    int m_hitProbability = 0;

public:
    /**
     * @brief This friend will print UnitProperty
     * 
     * @param o 
     * @param fred 
     * @return std::ostream& 
     */
    friend std::ostream &operator<<(std::ostream &o, CUnitProperty const &unitP);
    /**
     * @brief Get the Speed object
     * 
     * @return const int 
     */
    const int GetSpeed() const;

    /**
     * @brief Get the Hit Range object
     * 
     * @return const int 
     */
    const int GetHitRange() const;

    /**
     * @brief Get the Probability object
     * 
     * @return const int 
     */
    const int GetProbability() const;
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
