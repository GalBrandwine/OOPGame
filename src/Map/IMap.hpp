#pragma once
#include <map>
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

#include "IUnitMap.hpp"
#include "CUnitProperty.hpp"
#ifdef ShowDebugMap
#include <opencv2/highgui.hpp>
#endif

#define MAP_SIZE 100

class IMap
{
public:
    /**
    * @brief Remove this ID from map
    * 
    * @param id 
    * @return true If removed successfully
    * @return false Otherwise
    */
    virtual bool RemovePawn(int id) = 0;
    /**
    * @brief Find all neighbors given location and range
    * 
    * @param[in] range 
    * @param[in] my_location 
    * @param[out] neighbors std::vector<std::shared_ptr<IUnitMap>> & of all neighboors found.
    */
    virtual void FindNeighborsInRange(const int range, const CLocation &my_location, std::list<std::pair<float, IUnitMap *>> &neighbors) const = 0;

#ifdef ShowDebugMap
    virtual void ShowMap() = 0;
#endif
    virtual ~IMap(){};
};
