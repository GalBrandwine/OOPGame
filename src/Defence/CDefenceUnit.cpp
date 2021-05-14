#include "CDefenceUnit.hpp"

UnitTypes::UnitTypes CDefenceUnit::GetType() const
{
    return m_unitType;
}

int CDefenceUnit::GetId() const
{
    return m_id;
}

const CLocation &CDefenceUnit::GetStartLocation()
{
    return m_startLocation;
}

void CDefenceUnit::PerformTurn(std::map<int, CUnitProperty *> *properties)
{
    std::cout << "Im Defence unit, performing a turn"
              << "/n";
    return;
}
CDefenceUnit::CDefenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start)
{
}

CDefenceUnit::~CDefenceUnit()
{
}