#pragma once
#include "Unit.hpp"
#include "utils/utils.h"
#include "utils/CLocation.h"
#include "utils/CConstants.h"

/**
 * @brief 
 * 
 * * Anti-air system  -> Airplane
 * * Anti-tank system -> Tank
 * * Anti-ship system -> Ship
 */
static std::map<UnitTypes::UnitTypes, UnitTypes::UnitTypes> DefenseDict(
    {{UnitTypes::UnitTypes::AntiAir, UnitTypes::UnitTypes::Airplane},
     {UnitTypes::UnitTypes::AntiTank, UnitTypes::UnitTypes::Tank},
     {UnitTypes::UnitTypes::AntiShip, UnitTypes::UnitTypes::Ship}});

class CDefenceUnit : public Unit
{

public:
    /**
     * @brief Performs a turn given set of properties.
     * 
     * **Turn**
     * * Offence units:
     *     If the target is in the range - attack it according to the given probability.
     *     When the target is destroyed - remove it and the offence unit.
     *     If the target is not in range - advance towards the target with the given speed.
     * 
     * @param properties 
     */
    void PerformTurn(std::map<int, CUnitProperty *> *properties) override;

    /**
     * @brief Construct a new COffenceUnit::COffenceUnit object
     * 
     * @param unitType 
     * @param id 
     * @param start 
     * @param target 
     * @param aux_ptr 
     */
    CDefenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CAuxiliary *aux_ptr);
    ~CDefenceUnit();

private:
    /**
     * @brief Check if enemy within  range is an enemy I can kill
     * 
     * Defenc-system / Enemies relations:
     * * Anti-air system  -> Airplane
     * * Anti-tank system -> Tank
     * * Anti-ship system -> Ship
     * 
     * @param type 
     * @return true 
     * @return false 
     */
    bool canIDefendFromThisEnemy(UnitTypes::UnitTypes type) const;
};
