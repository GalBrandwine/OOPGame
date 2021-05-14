#pragma once
#include <memory>
#include "IUnitMap.hpp"
#include "IMap.hpp"
/**
 * @brief The battlefield takes place on a 100x100 size area (two-dimensional grid).
 * 
 */
#define MAP_SIZE 100
class Map : public IMap
{
private:
    cv::Mat m_map;
    

    cv::Mat m_debug_map;

public:
    /**
     * @brief Construct a new Map object
     * 
     * At construction time, I fill the map with pawns in the folowing method:
     * * Each pawn is a pixel on an RGB image (a.k.a the map), where I use the RGB channel for storring pawns information:
     *   *  Channel 0 - TBD
     *   *  Channel 1 - PawnType
     *   *  Channel 2 - PawnID
     * 
     * @note I could use 4D image If I need more information to store.
     * 
     * @param pawns list filled with initiated pawns
     */
    Map(std::list<IUnitMap *> &pawns);
    ~Map();
};
