#pragma once
#include <memory>
#include <map>
#include "CUnitProperty.hpp"
#include "IMap.hpp"
/**
 * @brief IUnit holds the PerformTurn interface that each Unit have to implement.
 * 
 */
class IUnit
{
public:
    virtual bool IsAlive() = 0;
    virtual void LoadMap(std::shared_ptr<IMap> map) = 0;
    /**
     * @brief Performs a turn under Derived class rules.
     * 
     * @param properties 
     */
    virtual void PerformTurn(std::map<int, CUnitProperty *> *properties) = 0;
    virtual ~IUnit(){};
};