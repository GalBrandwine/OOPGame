#include "COffenceUnit.hpp"

void COffenceUnit::LoadMap(std::shared_ptr<IMap> map)
{
    m_map = map;
}
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
    std::cout << "\nIm Offence unit of type: "
              << UnitTypes::to_string(m_unitType) << "\n";

    auto my_properties = (*properties)[m_unitType];

    std::cout << "\nMy properties are: " << *my_properties << "\n"
              << "Performing turn:\n";

    /** @brief Step 1:  
     * * Get all targets in range from map.
     * * Filter friendlies.
    */
    auto my_range = my_properties->GetHitRange();
    std::vector<std::shared_ptr<IUnitMap>> neighboors;
    /** @todo Add to unitMap the direction of the neighbor (in theta terms) */
    m_map->FindNeighborsInRange(my_range, m_startLocation, neighboors);

    m_aux->MoveUnit(&m_startLocation, &m_targetLocation, 3, 3, my_properties->GetSpeed());
    /** @todo Update debugMap with units current location. */

    /** @brief Step2: 
     * * If enemy is in range: 
     *   * Get enemy diractions.
     *   * * Can I move to this direction?
     *   * Attack it with probability to hit. 
     *   * If enemy destroyed:
     *   *  * Remove it and this offence unit from  the map.
     * * Else (enemy is not in range):
     *   * advance towards the target with the given speed.
     */

    // m_aux->MoveUnit()
    return;
}

COffenceUnit::COffenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target, CAuxiliary *aux_ptr)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start),
      m_targetLocation(target),
      m_aux(aux_ptr)
{
}

COffenceUnit::~COffenceUnit()
{
}