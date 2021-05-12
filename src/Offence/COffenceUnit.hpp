#pragma once
#include "IUnit.hpp"
#include "utils/utils.h"
#include "utils/CLocation.h"
#include "utils/CConstants.h"
class COffenceUnit : public IUnit
{
private:
    UnitTypes::UnitTypes m_unitType;
    int m_id;
    CLocation m_startLocation;
    CLocation m_targetLocation;

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
     * @brief Construct a new COffenceUnit object
     * 
     * @param unitType 
     * @param id 
     * @param startLocation 
     * @param targetLOcation 
     */
    COffenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation startLocation, CLocation targetLOcation);
    ~COffenceUnit();
};
