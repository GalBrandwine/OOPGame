#include "COffenceUnit.hpp"

UnitTypes::UnitTypes COffenceUnit::GetType() const
{
    return m_unitType;
}

int COffenceUnit::GetId() const
{
    return m_id;
}

const CLocation &COffenceUnit::GetStartLocation()
{
    return m_startLocation;
};

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