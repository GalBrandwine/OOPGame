#include "COffenceUnit.hpp"

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
UnitTypes::Side COffenceUnit::GetSide() const
{
    return m_Side;
}

/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
void COffenceUnit::LoadMap(std::shared_ptr<IMap> map)
{
    m_map = map;
}
/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
UnitTypes::UnitTypes COffenceUnit::GetType() const
{
    return m_unitType;
}
/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
int COffenceUnit::GetId() const
{
    return m_id;
}
/** @todo Implement Unit that implements IUnit. So that Defence and  offence will inherit from it.*/
const CLocation &COffenceUnit::GetStartLocation()
{
    return m_startLocation;
};

void COffenceUnit::SetKilled()
{
    m_isAlive = false;
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
        /** @brief Remove duplicates.
         * I know that there are probably better solutions, this is it for now.
         */
        int index_outer = 0;
        for (const auto &thetha_neighboor : m_neighboors)
        {
            int index_inner = 0;
            for (const auto &thetha_neighboor_inner : m_neighboors)
            {
                if (thetha_neighboor.second == thetha_neighboor_inner.second)
                {
                    if (index_inner > index_outer)
                    {
                        m_neighboors.erase(m_neighboors.begin() + index_inner);
                    }
                }
                index_inner++;
            }
            index_outer++;
        }

        int index = 0;
        for (const auto &thetha_neighboor : m_neighboors)
        {

            auto neighboor = thetha_neighboor.second;

            /** @brief This is me. Continue filtering.. */
            if (neighboor->GetId() == m_id)
            {
                // std::cout << "This is me (Due to a known bug, this may be printed a lot of times). Continue filtering.. \n";
                m_neighboors.erase(m_neighboors.begin() + index);
                continue;
            }
            /** @brief This neighboor and I are on the same side. Continue filtering */
            else if (neighboor->GetSide() == m_Side)
            {
                std::cout << "This neighboor and I are on the same side. Continue filtering \n";
                m_neighboors.erase(m_neighboors.begin() + index);
                continue;
            }

            auto type = neighboor->GetType();
            std::cout << "\nFound neighboor "
                      << "In angel: " << thetha_neighboor.first
                      << " This neighboor is of type: " << UnitTypes::to_string(neighboor->GetType())
                      << " And its ID: " << thetha_neighboor.second->GetId()
                      << "\n";

            index++;
        }
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
        std::cout << "With step[" << m_targetDirection.x << "," << m_targetDirection.y << "]\n";
        m_aux->MoveUnit(&m_startLocation, &m_targetLocation, m_targetDirection.x, m_targetDirection.y, my_properties->GetSpeed());
    }

    /** @todo Update debugMap with units current location. */
    m_map->ShowMap();

    return;
}

COffenceUnit::COffenceUnit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target, CAuxiliary *aux_ptr)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start),
      m_targetLocation(target),
      m_aux(aux_ptr),
      m_Side(UnitTypes::Side::Offence)
{
}

COffenceUnit::~COffenceUnit()
{
}