#include "CDefenceUnit.hpp"

/**
 * @note I probably should have moved it up to Unit base class.
 */
bool CDefenceUnit::canIDefendFromThisEnemy(UnitTypes::UnitTypes type) const
{
    auto it = DefenseDict.find(m_unitType);
    if (it == DefenseDict.end())
    {
        std::cerr << "This enemy is not in the defend list. I dont know this enemy!\n"
                  << "Cant intercept.\n";
        return false;
    }

    auto it2 = std::find(it->second.begin(), it->second.end(), type);
    if (it2 != it->second.end())
    {
        std::cout << "I know this enemy. And I can intercept! returning true\n";
        return true;
    }
    else
    {
        std::cout << "I know this enemy. BUT I cant intercept! returning false\n";
        return false;
    }
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
        return;
    }

    auto my_properties = (*properties)[m_unitType];
    std::cout << "\nMy properties are:\n"
              << *my_properties << "\n"
              << "\nPerforming turn\n";

    /**
     * @brief Setup
     * 
     */
    m_neighboors.clear();

    /** @brief Step 1:  
     * * Get all targets in range from map.
     */
    m_map->FindNeighborsInRange(my_properties->GetHitRange(), m_startLocation, m_neighboors);

    /**
     * @brief Step 2:
     * * Filter friendlies.
     */
    if (m_neighboors.size() != 0)
    {

        removeDuplicates();
        removeFriendlies();
    }

    /** @brief Check on neighboors more time. Maybe I Filtered everyone (In a case where all the neighboors were friendlies) */
    if (m_neighboors.size() != 0)
    {
        /**
         * @brief Step 3
         * By now all the nighboors left are enemies within range:
         * 
         * @note According to story:
         *  Bolvatians have multiple tanks, planes and ships. They want to destroy all the
         *  Deboryans buildings and units:
         * 
         * * Anti-air system  -> Airplane
         * * Anti-tank system -> Tank
         * * Anti-ship system -> Ship
         */

        int index = 0;
        for (const auto &thetha_neighboor : m_neighboors)
        {
            auto type = (thetha_neighboor.second)->GetType();

            if (!canIDefendFromThisEnemy(type))
                continue;

            auto attack = m_aux->TryHitOpponent(my_properties->GetProbability());
            if (attack == 1)
            {
                std::cout << "\nAttacking neighboor!\n"
                          << "This neighboor is of type: " << UnitTypes::to_string(type)
                          << " And its ID: " << thetha_neighboor.second->GetId()
                          << "\n";

                /** @note Now I need to:
                 *  * Remove this neighboor from map .
                 *  * Kill him.
                 *  * Kill myself (which means I need to remove myself from the map also..)
                 *  * And break the loop. 
                 */
                if (m_map->RemovePawn(thetha_neighboor.second->GetId()))
                {
                    std::cout << "Successfully removed this neighboor from the map!\n";
                }
                if (m_map->RemovePawn(m_id))
                {
                    std::cout << "Successfully removed myself from the map!\n";
                }
                return;
            }
        }
    }

#ifdef ShowDebugMap
    /** @todo Update debugMap with units current location. */
    m_map->ShowMap();
#endif
    return;
}

CDefenceUnit::CDefenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CAuxiliary *aux_ptr)
    : Unit(unitType, id, start, aux_ptr, UnitTypes::Side::Defence)
{
}

CDefenceUnit::~CDefenceUnit()
{
}