#include "Map.hpp"
Map::Map(std::list<IUnitMap *> &pawns)
    : m_map(cv::Mat(MAP_SIZE, MAP_SIZE, CV_16FC3, cv::Scalar(0, 0, 0))),
      m_debug_map(cv::Mat(MAP_SIZE, MAP_SIZE, CV_8UC3, cv::Scalar(0, 0, 0)))
{

    std::cout << "Setting " << pawns.size() << " pawns on the map.\n";
    for (const auto &pawn : pawns)
    {
        cv::Vec3b pawn_on_map; /** @brief BGR Channel usage: CH0 - TBD, CH1 - Type, CH2 - ID */
        pawn_on_map[0] = 0;
        pawn_on_map[1] = pawn->GetType();
        pawn_on_map[2] = pawn->GetId();
        m_map.at<cv::Vec3b>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y())) = pawn_on_map;

        pawn_on_map[1] = UnitTypes::to_color(pawn->GetType());
        m_debug_map.at<cv::Vec3b>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y())) = pawn_on_map;
    }

#ifdef ShowDebugMap
    cv::imshow("Map", m_debug_map);
    cv::waitKey(0);
#endif
}

Map::~Map()
{
}