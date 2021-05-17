#pragma once
#include <memory>
#include "IUnitMap.hpp"
#include "IMap.hpp"
/**
 * @brief The battlefield takes place on a 100x100 size area (two-dimensional grid).
 * 
 */

/**
 * @brief Map channel to pawn attribute
 * 
 */
enum CHANNELS
{
    SIDE,
    TYPE,
    ID
};

class Map : public IMap
{
private:
    int m_map_size;
    cv::Mat m_map;
    cv::Mat m_debug_map;
    /** @brief Store a reference to pawns, 
     * so when GameAdmin is maintaining the players lists it will be updates here.
    */
    std::list<IUnitMap *> &m_all_pawns;

    /** @brief BGR Channel usage: 
     * * CH0 - TBD
     * * CH1 - Type
     * * CH2 - ID
    */
    void FillMap();

public:
    /**
    * @brief Remove this ID from map
    * 
    * @param id 
    * @return true If removed successfully
    * @return false Otherwise
    */
    bool RemovePawn(int id) override;

    /**
     * @brief Find neighboors
     * 
     * @param range 
     * @param my_location 
     * @param neighbors 
     */
    void FindNeighborsInRange(const int range, const CLocation &my_location, std::list<std::pair<float, IUnitMap *>> &neighbors) const override;

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
     * @param map_size 
     */
    Map(std::list<IUnitMap *> &pawns, int map_size = MAP_SIZE);
    ~Map();

#ifdef ShowDebugMap
    void ShowMap() override;
#endif
};
