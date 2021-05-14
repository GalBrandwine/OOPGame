#include "CDefenceUnit.hpp"

void CDefenceUnit::LoadMap(std::shared_ptr<IMap> map)
{
    m_map = map;
}
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
      m_startLocation(start)
{
}

CDefenceUnit::~CDefenceUnit()
{
}