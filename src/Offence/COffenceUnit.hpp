#pragma once

#include "Unit.hpp"
#include "utils/utils.h"
#include "utils/CLocation.h"
#include "utils/CConstants.h"
#include "utils/CAuxiliary.h"

class COffenceUnit : public Unit
{
private:
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
};
