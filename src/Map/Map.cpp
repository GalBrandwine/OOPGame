#include "Map.hpp"
#include <cstdint>

#ifdef ShowDebugMap
const void Map::ShowMap() const
{
    cv::imshow("Map", m_debug_map);
    cv::waitKey(10);
}
#endif

const void Map::FindNeighborsInRange(const int range, const CLocation &my_location, std::vector<std::pair<float, IUnitMap *>> &neighbors) const
{
    cv::Point2d my_position(my_location.X(), my_location.Y());

#ifdef ShowDebugMap
    cv::Mat debug;
    m_debug_map.copyTo(debug);
    cv::circle(debug, my_position, range, cv::Scalar(200), 1);
#endif

    /** @note I could iterate over the image itself with X,Y values. Bu this way I iterate on less pixels */
    for (int r_i = range; r_i > 0; r_i--) /** @brief Circle inwards O(range<=100 ~ 1)*/
    {
        for (float theta = 0; theta <= 2 * CV_PI; theta += 0.05) /** @brief O(theta=2Phi ~ 1) */
        {
            auto Px_delta = cos(theta) * r_i;
            auto Py_delta = sin(theta) * r_i;
            cv::Vec3i new_loc(my_position.x + Px_delta, my_position.y + Py_delta, 255);

            auto possible_neighbor = m_map.at<cv::Vec3i>(new_loc[1], new_loc[0]);

            /**
             * @brief Reminder: 
             * At initiation time, I In stored units ID CH2
             * 
             */
            if (possible_neighbor[CHANNELS::ID] != 0)
            {
                /**
                 * @brief Get this neighboor from the pawns list stored inside Map
                 * O(|pawns| ~ n)
                 */
                auto it = std::find_if(m_all_pawns.begin(), m_all_pawns.end(),
                                       [possible_neighbor](IUnitMap *pawnOnMap) {
                                           return pawnOnMap->GetId() == possible_neighbor[CHANNELS::ID];
                                       });

                if (it == m_all_pawns.end())
                {
                    std::cerr << "\n\n******** Found a neighboor that is not in the neighboor list - Thats not possible! ********* \n\n";
                    return;
                }
                auto t = std::make_pair(theta, *it);
                neighbors.push_back(t);
            }

#ifdef ShowDebugMap
            // std::cout
            //     << "Current theta: " << theta << "\n";
            // std::cout << " Current point: " << new_loc << "\n";

            /**
             * @brief Paint on the debug image current visited pixel.
             * 
             */
            debug.at<cv::Vec3b>(new_loc[1], new_loc[0]) = new_loc;

            cv::imshow("Map_my_location", debug);
            cv::waitKey(5);
#endif
        }
    }

    // cv::imshow("Map_my_location", debug);
    // cv::waitKey(0);
}
Map::Map(std::list<IUnitMap *> &pawns)
    : m_map(cv::Mat(MAP_SIZE, MAP_SIZE, CV_32SC3, cv::Scalar(0, 0, 0))),
      m_debug_map(cv::Mat(MAP_SIZE, MAP_SIZE, CV_8UC3, cv::Scalar(0, 0, 0)))
{

    std::cout << "Setting " << pawns.size() << " pawns on the map.\n";
    for (const auto &pawn : pawns)
    {
        /** @brief BGR Channel usage: 
         * * CH0 - TBD
         * * CH1 - Type
         * * CH2 - ID
         */
        cv::Vec3i pawn_on_map;
        pawn_on_map[CHANNELS::TBD] = 0;
        pawn_on_map[CHANNELS::TYPE] = pawn->GetType();
        pawn_on_map[CHANNELS::ID] = pawn->GetId();

        /** @todo Add protection agains pawns that are placed outside the map. */
        m_map.at<cv::Vec3i>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y())) = pawn_on_map;

        pawn_on_map[1] = UnitTypes::to_color(pawn->GetType());
        m_debug_map.at<cv::Vec3i>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y())) = pawn_on_map;
    }

    m_all_pawns = pawns;
    // #ifdef ShowDebugMap
    //     cv::imshow("Map", m_debug_map);
    //     cv::waitKey(0);
    // #endif
}

Map::~Map()
{
}