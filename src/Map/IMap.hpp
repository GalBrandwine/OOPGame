#pragma once
#include <map>
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

#include "IUnitMap.hpp"
#include "utils/CLocation.h"
#ifdef ShowDebugMap
#include <opencv2/highgui.hpp>
#endif

class IMap
{
public:
        /**
         * @brief Find all neighbors given location and range
         * 
         * @param[in] range 
         * @param[in] my_location 
         * @param[out] neighbors std::vector<std::shared_ptr<IUnitMap>> & of all neighboors found.
         */
        virtual const void FindNeighborsInRange(const int range, const CLocation &my_location, std::vector<std::shared_ptr<IUnitMap>> &neighbors) const = 0;

#ifdef ShowDebugMap
        virtual const void ShowMap() const = 0;
#endif
        virtual ~IMap(){};
};
