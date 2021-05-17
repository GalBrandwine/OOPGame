#include "Unit.hpp"

void Unit::removeFriendlies()
{
    for (auto it_thetha_neighboor = m_neighboors.begin(); it_thetha_neighboor != m_neighboors.end(); /* don't increment here */)
    {
        /** @brief This is me. Continue filtering.. */
        if ((it_thetha_neighboor)->second->GetId() == m_id)
        {
            // std::cout << "This is me (Due to a known bug, this may be printed a lot of times). Continue filtering.. \n";
            it_thetha_neighboor = m_neighboors.erase(it_thetha_neighboor);
            continue;
        }
        /** @brief This neighboor and I are on the same side. Continue filtering */
        else if ((it_thetha_neighboor)->second->GetSide() == m_Side)
        {
            std::cout << "This neighboor and I are on the same side. Continue filtering \n";
            it_thetha_neighboor = m_neighboors.erase(it_thetha_neighboor);
            continue;
        }
        auto type = (it_thetha_neighboor)->second->GetType();
        std::cout << "\nFound neighboor "
                  << "In angel: " << (it_thetha_neighboor)->first
                  << " This neighboor is of type: " << UnitTypes::to_string((it_thetha_neighboor)->second->GetType())
                  << " And its ID: " << (it_thetha_neighboor)->second->GetId()
                  << "\n";

        ++it_thetha_neighboor;
    }
}

void Unit::removeDuplicates()
{

    for (auto it_thetha_neighboor_outer = m_neighboors.begin(); it_thetha_neighboor_outer != m_neighboors.end(); /* don't increment here */)
    {
        auto neighboor_ptr = (it_thetha_neighboor_outer)->second;

        for (auto it_thetha_neighboor_inner = m_neighboors.begin(); it_thetha_neighboor_inner != m_neighboors.end(); /* don't increment here */)
        {

            /** @brief See if this neighboor is stored more than one time. */
            if (neighboor_ptr == (it_thetha_neighboor_inner)->second)
            {

                /** @brief Make sure this neighboor is not the same neighboor from the outer loop */
                auto distance = std::distance(it_thetha_neighboor_outer, it_thetha_neighboor_inner);
                if (distance > 0)
                {
                    it_thetha_neighboor_inner = m_neighboors.erase(it_thetha_neighboor_inner);
                    continue;
                }
            }
            ++it_thetha_neighboor_inner;
        }
        ++it_thetha_neighboor_outer;
    }
}

UnitTypes::Side Unit::GetSide() const
{
    return m_Side;
}

void Unit::LoadMap(std::shared_ptr<IMap> map)
{
    m_map = map;
}

UnitTypes::UnitTypes Unit::GetType() const
{
    return m_unitType;
}

int Unit::GetId() const
{
    return m_id;
}

const CLocation &Unit::GetStartLocation()
{
    return m_startLocation;
};

void Unit::SetKilled()
{
    m_isAlive = false;
}

Unit::Unit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target, CAuxiliary *aux_ptr, UnitTypes::Side side)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start),
      m_targetLocation(target),
      m_aux(aux_ptr),
      m_Side(side)
{
}

Unit::Unit(UnitTypes::UnitTypes unitType, int id, CLocation start, CAuxiliary *aux_ptr, UnitTypes::Side side)
    : m_unitType(unitType),
      m_id(id),
      m_startLocation(start),
      m_targetLocation{DEFAULT_LOCATION, DEFAULT_LOCATION},
      m_aux(aux_ptr),
      m_Side(side)
{
}
Unit::~Unit()
{
}