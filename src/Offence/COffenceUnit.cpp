#include "COffenceUnit.hpp"

void COffenceUnit::PerformTurn(std::map<int, CUnitProperty *> *properties)
{
    std::cout << "Im Offence unit, performing a turn"
              << "/n";
    return;
}

COffenceUnit::COffenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start),
      m_targetLocation(target)
{
}

COffenceUnit::~COffenceUnit()
{
}