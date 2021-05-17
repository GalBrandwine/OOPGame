#pragma once

#include "IUnit.hpp"
#include "IUnitMap.hpp"
#include "utils/CAuxiliary.h"
class Unit : public IUnit, public IUnitMap
{
private:
    /* data */
protected:
    bool m_isAlive = true;
    Cdirection m_targetDirection;

    /** @brief Remove duplicates.
     * I know that there are probably better solutions, this is it for now.
     *
     * @note This is \f$O(n^2)\f$ complexity 
     * 
     * @code {.cpp}
     * for (auto it_thetha_neighboor_outer = m_neighboors.begin(); it_thetha_neighboor_outer != m_neighboors.end();)
     * {
     *     auto neighboor_ptr = (it_thetha_neighboor_outer)->second;
     * 
     *     for (auto it_thetha_neighboor_inner = m_neighboors.begin(); it_thetha_neighboor_inner != m_neighboors.end();)
     *     {
     *    
     *         if (neighboor_ptr == (it_thetha_neighboor_inner)->second)
     *         {
     * 
     *             auto distance = std::distance(it_thetha_neighboor_outer, it_thetha_neighboor_inner);
     *             if (distance > 0)
     *             {
     *                 it_thetha_neighboor_inner = m_neighboors.erase(it_thetha_neighboor_inner);
     *                 continue;
     *             }
     *         }
     *         ++it_thetha_neighboor_inner;
     *     }
     *     ++it_thetha_neighboor_outer;
     * }
     * @endcode
     * 
     */
    void removeDuplicates();
    /**
     * @brief Remove Friendlies.
     * 
     * @note Same as removeDuplicates(), this it \f$O(n^2)\f$ algorithm
     *
     * @code {.cpp} 
     * for (auto it_thetha_neighboor = m_neighboors.begin(); it_thetha_neighboor != m_neighboors.end();)
     * {
     *    if ((it_thetha_neighboor)->second->GetId() == m_id)
     *    {
     *        it_thetha_neighboor = m_neighboors.erase(it_thetha_neighboor);
     *        continue;
     *    }
     *    else if ((it_thetha_neighboor)->second->GetSide() == m_Side)
     *    {
     *        it_thetha_neighboor = m_neighboors.erase(it_thetha_neighboor);
     *        continue;
     *    }
     *    ++it_thetha_neighboor;
     * }
     * @endcode
     */
    void removeFriendlies();

    /**
     * @brief This member hold all neighbors within range. for this turn.
     * Its a vector of pairs.
     * * Element 0: The angle [rad] of the neighboor.
     * * Element 1: A shared pointer to the neighboor.
     * 
     * @note Neighboors are extracted from the map, hence they are represented by IUnitMap.
     */
    std::list<std::pair<float, IUnitMap *>> m_neighboors;

    std::shared_ptr<IMap> m_map;
    UnitTypes::UnitTypes m_unitType;
    UnitTypes::Side m_Side;
    int m_id;
    CLocation m_startLocation;
    CLocation m_targetLocation;
    CAuxiliary *m_aux;

public:
    /**
     * @brief Method decleration ONLY! 
     * Performs a turn given set of properties.
     * 
     * @note This must be implemented in the Unit siblings (Offense or Defense)
     * @param properties 
     */
    virtual void PerformTurn(std::map<int, CUnitProperty *> *properties) = 0;
    bool IsAlive() override { return m_isAlive; };
    void SetKilled() override;
    void LoadMap(std::shared_ptr<IMap> map) override;
    UnitTypes::UnitTypes GetType() const override;
    int GetId() const override;
    const CLocation &GetStartLocation() override;
    UnitTypes::Side GetSide() const override;
    Unit(UnitTypes::UnitTypes unitType, int id, CLocation start, CLocation target, CAuxiliary *aux_ptr, UnitTypes::Side side);
    Unit(UnitTypes::UnitTypes unitType, int id, CLocation start, CAuxiliary *aux_ptr, UnitTypes::Side side);
    ~Unit();
};
