#pragma once
#include "IUnit.hpp"
#include "IUnitMap.hpp"
#include "utils/utils.h"
#include "utils/CLocation.h"
#include "utils/CConstants.h"

class CDefenceUnit : public IUnit, public IUnitMap
{
private:
    std::shared_ptr<IMap> m_map;
    int m_id;
    UnitTypes::UnitTypes m_unitType;
    CLocation m_startLocation;

public:
    void LoadMap(std::shared_ptr<IMap> map) override;
    UnitTypes::UnitTypes GetType() const override;
    int GetId() const override;
    const CLocation &GetStartLocation() override;

    /**
     * @brief Performs a turn given set of properties.
     * 
     * **Turn**
     * * Defense units:
     *     If there is an offence unit in range - intercept it according to the given
     *     probability.  
     *     When the offence unit is destroyed - remove it.
     * 
     * @param properties 
     */
    void PerformTurn(std::map<int, CUnitProperty *> *properties) override;
    CDefenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start);
    ~CDefenceUnit();
};
