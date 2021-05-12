#include "CDefenceUnit.hpp"

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