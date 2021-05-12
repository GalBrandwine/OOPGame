#pragma once
#include <map>
#include "CUnitProperty.hpp"

/**
 * @brief IUnit holds the PerformTurn interface that each Unit have to implement.
 * 
 */
class IUnit
{
public:
    /**
     * @brief Performs a turn under Derived class rules.
     * 
     * @param properties 
     */
    virtual void PerformTurn(std::map<int, CUnitProperty *> *properties){};
    ~IUnit(){};
};