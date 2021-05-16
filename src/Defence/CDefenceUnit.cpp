#include "CDefenceUnit.hpp"

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
UnitTypes::Side CDefenceUnit::GetSide() const
{
    return m_Side;
}

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
void CDefenceUnit::LoadMap(std::shared_ptr<IMap> map)
{
    m_map = map;
}

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
UnitTypes::UnitTypes CDefenceUnit::GetType() const
{
    return m_unitType;
}

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
int CDefenceUnit::GetId() const
{
    return m_id;
}

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
const CLocation &CDefenceUnit::GetStartLocation()
{
    return m_startLocation;
}

void CDefenceUnit::SetKilled()
{
    m_isAlive = false;
}
void CDefenceUnit::PerformTurn(std::map<int, CUnitProperty *> *properties)
{
    if (!m_isAlive)
        return;
    std::cout << "\nIm Defence unit of type: "
              << UnitTypes::to_string(m_unitType) << "\n";

    if (m_unitType == UnitTypes::UnitTypes::Building)
    {
        std::cout << "Im a building, I cant move. Thus no properties.\n";
    }
    else
    {
        auto my_properties = (*properties)[m_unitType];
        std::cout << "\nMy properties are:\n"
                  << *my_properties << "\n";
    }

    std::cout << "\nPerforming turn\n";
    return;
}

CDefenceUnit::CDefenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start),
      m_Side(UnitTypes::Side::Defence) /** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
{
}

CDefenceUnit::~CDefenceUnit()
{
}