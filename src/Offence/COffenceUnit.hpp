#pragma once

#include "Unit.hpp"
#include "utils/utils.h"
#include "utils/CLocation.h"
#include "utils/CConstants.h"
#include "utils/CAuxiliary.h"

#ifdef UtiliseBonus
/**
 * @brief OffenceDict Targeting dictionary.
 * 
 * @note This also implements the bonus!
 * 
 * Airplane            -> Anti-air system, building
 * Tank                -> Anti-tank system, building
 * Ship                -> Anti-ship system, building
 */
static std::map<UnitTypes::UnitTypes, std::vector<UnitTypes::UnitTypes>> OffenceDict(
    {{UnitTypes::UnitTypes::Airplane, std::vector<UnitTypes::UnitTypes>{UnitTypes::UnitTypes::AntiAir, UnitTypes::UnitTypes::Building}},
     {UnitTypes::UnitTypes::Tank, std::vector<UnitTypes::UnitTypes>{UnitTypes::UnitTypes::AntiTank, UnitTypes::UnitTypes::Building}},
     {UnitTypes::UnitTypes::Ship, std::vector<UnitTypes::UnitTypes>{UnitTypes::UnitTypes::AntiShip, UnitTypes::UnitTypes::Building}}});
#else
/**
 * @brief OffenceDict Targeting dictionary.
 * 
 * @note No bonus here
 * 
 * Airplane            -> Anti-air, anti-tank, anti-ship systems, building
 * Tank                -> Anti-air, anti-tank, anti-ship systems, building
 * Ship                -> Anti-air, anti-tank, anti-ship systems, building
 * 
 */
static std::map<UnitTypes::UnitTypes, std::vector<UnitTypes::UnitTypes>> OffenceDict(
    {{UnitTypes::UnitTypes::Airplane,  std::vector<UnitTypes::UnitTypes>{UnitTypes::UnitTypes::AntiAir, UnitTypes::UnitTypes::AntiTank, UnitTypes::UnitTypes::AntiShip, UnitTypes::UnitTypes::Building}},
     {UnitTypes::UnitTypes::Tank,      std::vector<UnitTypes::UnitTypes>{UnitTypes::UnitTypes::AntiAir, UnitTypes::UnitTypes::AntiTank, UnitTypes::UnitTypes::AntiShip, UnitTypes::UnitTypes::Building}},
     {UnitTypes::UnitTypes::Ship,      std::vector<UnitTypes::UnitTypes>{UnitTypes::UnitTypes::AntiAir, UnitTypes::UnitTypes::AntiTank, UnitTypes::UnitTypes::AntiShip, UnitTypes::UnitTypes::Building}}});
#endif

class COffenceUnit : public Unit
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
   COffenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target, CAuxiliary *aux_ptr);
   ~COffenceUnit();

private:
   /**
     * @brief Check if enemy within  range is an enemy I can kill
     * 
     * @note This also implements the bonus!
     * 
     * Offense\target relations:
     * * Airplane   -> Anti-air system,Building
     * * Tank       -> Anti-tank system,Building
     * * Ship       -> Anti-ship system,Building
     * 
     * @param type 
     * @return true 
     * @return false 
     */
   bool canIAttackThisEnemy(UnitTypes::UnitTypes type) const;
};
