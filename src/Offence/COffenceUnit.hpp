#pragma once
#include "IUnit.hpp"
#include "IUnitMap.hpp"
#include "utils/utils.h"
#include "utils/CLocation.h"
#include "utils/CConstants.h"
#include "utils/CAuxiliary.h"

class COffenceUnit : public IUnit, public IUnitMap
{
private:
    /** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
    bool m_isAlive = true;
    Cdirection m_targetDirection;
    /**
     * @brief This member hold all neighbors within range. for this turn.
     * Its a vector of pairs.
     * * Element 0: The angle [rad] of the neighboor.
     * * Element 1: A shared pointer to the neighboor.
     * 
     * @note Neighboors are extracted from the map, hence they are represented by IUnitMap.
     */
    std::vector<std::pair<float, IUnitMap *>> m_neighboors;

    std::shared_ptr<IMap> m_map;
    UnitTypes::UnitTypes m_unitType;
    UnitTypes::Side m_Side;
    int m_id;
    CLocation m_startLocation;
    CLocation m_targetLocation;
    CAuxiliary *m_aux;

public:
    /** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
    bool IsAlive() override { return m_isAlive; };
    void SetKilled() override;
    void LoadMap(std::shared_ptr<IMap> map) override;
    UnitTypes::UnitTypes GetType() const override;
    int GetId() const override;
    const CLocation &GetStartLocation() override;
    UnitTypes::Side GetSide() const override;
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
