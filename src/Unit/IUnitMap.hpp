#pragma once
#include "utils/CLocation.h"
#include "utils/CConstants.h"
/**
 * @brief IUnitMap expose the interface relevant to Map
 * 
 */
class IUnitMap
{
public:
    virtual int GetId() const = 0;
    virtual UnitTypes::UnitTypes GetType() const = 0;
    virtual const CLocation &GetStartLocation() = 0;
    virtual ~IUnitMap(){};
};