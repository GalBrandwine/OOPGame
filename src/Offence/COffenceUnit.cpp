#include "COffenceUnit.hpp"

/**
 * @note I probably should have moved it up to Unit base class.
 */
bool COffenceUnit::canIAttackThisEnemy(UnitTypes::UnitTypes type) const
{
    auto it = OffenceDict.find(m_unitType);
    if (it == OffenceDict.end())
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

void COffenceUnit::PerformTurn(std::map<int, CUnitProperty *> *properties)
{
    if (!m_isAlive)
        return;

    std::cout << "\nIm Offence unit of type: "
              << UnitTypes::to_string(m_unitType) << "\n";

    auto my_properties = (*properties)[m_unitType];

    std::cout << "\nMy properties are: " << *my_properties << "\n"
              << "Performing turn:\n";

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

    /** @brief Check one neighboors more time. Maybe I Filtered everyone (In a case where all the neighboors were friendlies) */
    if (m_neighboors.size() != 0)
    {
        /**
         * @brief Step 3
         * By now all the nighboors left are enemies within range:
         * * If enemy is in range: 
         *   * Attack it with probability to hit. 
         *   * If enemy destroyed:
         *   *  * Remove it and this offence unit from  the map.
         * 
         * @note According to story:
         *  Bolvatians have multiple tanks, planes and ships. They want to destroy all the
         *  Deboryans buildings and units:
         * 
         * * Airplane -> Anti-air, anti-tank, anti-ship systems, building
         * * Tank     -> Anti-air, anti-tank, anti-ship systems, building
         * * Ship     -> Anti-air, anti-tank, anti-ship systems, building
         */

        int index = 0;
        for (const auto &thetha_neighboor : m_neighboors)
        {
            auto type = (thetha_neighboor.second)->GetType();
            if (!canIAttackThisEnemy(type))
                return;

            auto attack = m_aux->TryHitOpponent(my_properties->GetProbability());
            if (attack == 1)
            {
                std::cout << "\nAttacking neighboor!\n"
                          << "This neighboor is of type: " << UnitTypes::to_string(type)
                          << " And its ID: " << thetha_neighboor.second->GetId()
                          << "\n";

                /** @todo Now I need to:
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

    /** @brief I filtered all the neighboors, and no enemies in sight. Advancing to designated enemy! */
    else
    {
        /** @brief Step4: 
        * * Get enemy diractions.
        * * * Can I move to this direction?
        * * Else (I passed my designated enemy):
        *   * Remove myself from game
        */
        auto x = m_targetLocation.X() - m_startLocation.X();
        auto y = m_targetLocation.Y() - m_startLocation.Y();

        std::cout << "My ID: " << m_id << " My current position: [" << m_startLocation.X() << "," << m_startLocation.Y() << "]. Moving toward target: [" << m_targetLocation.X() << "," << m_targetLocation.Y() << "]:\n";
        std::cout << "[" << x << "," << y << "]\n";

        m_aux->GetDirection(&m_startLocation, &m_targetLocation, &m_targetDirection);
        std::cout << "With step [" << m_targetDirection.x << "," << m_targetDirection.y << "]\n";

        m_aux->MoveUnit(&m_startLocation, &m_targetLocation, m_targetDirection.x, m_targetDirection.y, my_properties->GetSpeed(), MAP_SIZE);
    }

#ifdef ShowDebugMap
    /** @todo Update debugMap with units current location. */
    m_map->ShowMap();
#endif
    return;
}

COffenceUnit::COffenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target, CAuxiliary *aux_ptr)
    : Unit(unitType, id, start, target, aux_ptr, UnitTypes::Side::Offence)
{
}

COffenceUnit::~COffenceUnit()
{
}