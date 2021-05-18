#include "Map.hpp"
#include <cstdint>

#ifdef ShowDebugMap
void Map::ShowMap()
{
    FillMap();
    cv::imshow("Map", m_debug_map);
    cv::waitKey(10);
}
#endif

bool Map::RemovePawn(int id)
{
    int index = 0;
    auto it = std::find_if(m_all_pawns.begin(), m_all_pawns.end(),
                           [&index, id](IUnitMap *pawnOnMap) {
                               auto predicate = pawnOnMap->GetId() == id;
                               if (predicate)
                               {
                                   std::cout << "**************************************** Removing pawn ID: " << id;
                               }

                               return predicate;
                           });

    if (it == m_all_pawns.end())
    {
        std::cout << "\n\n******** Could not find given ID! ********* \n\n";
        return false;
    }

    (*it)->SetKilled();
    m_all_pawns.erase(it);

    /** @brief Remove it from map */
    for (cv::MatIterator_<cv::Vec3i> matIt = m_map.begin<cv::Vec3i>(); matIt != m_map.end<cv::Vec3i>(); ++matIt)
    {
        // std::cout << "Visiting pixel: " << (*matIt);
        if ((*matIt)[CHANNELS::ID] == id)
        {
            std::cout << ". Pixel reset success!\n";
            (*matIt)[CHANNELS::ID] = 0;
            (*matIt)[CHANNELS::TYPE] = 0;
        }
        else
            std::cout << "\n";
    }

    FillMap();
    return true;
}

void Map::FindNeighborsInRange(const int range, const CLocation &my_location, std::list<std::pair<float, IUnitMap *>> &neighbors) const
{
    cv::Point2d my_position(my_location.X(), my_location.Y());

#ifdef ShowDebugMap
    cv::Mat debug;
    m_debug_map.copyTo(debug);
    cv::circle(debug, my_position, range + 1, cv::Scalar(255, 0, 0), 1);
#endif

    /** @note I could iterate over the image itself with X,Y values. But this way I iterate on less pixels */
    for (int r_i = range; r_i > 0; r_i--) /** @brief Circle inwards * \f$O(range<=100 ~ 1)\f$*/
    {
        for (float theta = 0; theta <=2 * CV_PI; theta += 0.05) /** @brief \f$O(theta=2Phi ~ 1)\f$ */
        {
            auto Px_delta = cos(theta) * r_i;
            auto Py_delta = sin(theta) * r_i;
            cv::Vec3i new_loc(my_position.x + Px_delta, my_position.y + Py_delta, 255);

            if (new_loc[0] > m_map_size or new_loc[0] < 0 or new_loc[1] > m_map_size or new_loc[1] < 0)
            {
                std::cerr << " Out of bounds, continueing to next pixel.\n";
                continue;
            }

            const auto &possible_neighbor = m_map.at<cv::Vec3i>(new_loc[1], new_loc[0]);

            /**
             * @brief Reminder: 
             * At initiation time, I In stored units ID CH2
             * 
             */
            if (possible_neighbor[CHANNELS::ID] != 0)
            {
                /**
                 * @brief Get this neighboor from the pawns list stored inside Map
                 * \f$O(|pawns| ~ n)\f$
                 */
                auto it = std::find_if(m_all_pawns.begin(), m_all_pawns.end(),
                                       [&possible_neighbor](IUnitMap *pawnOnMap) {
                                           if (pawnOnMap == nullptr)
                                           {
                                               std::cout << "Hit null! \n";
                                               return false;
                                           }

                                           return pawnOnMap->GetId() == possible_neighbor[CHANNELS::ID];
                                       });

                if (it == m_all_pawns.end())
                {
                    std::cerr << "\n\n******** Found a neighboor that is not in the neighboor list - Thats not possible! ********* \n\n";
                    return;
                }
                neighbors.push_back(std::make_pair(theta, *it));
            }

#ifdef ShowDebugMap
            /**
             * @brief Paint on the debug image current visited pixel.
             * 
             */
            auto color = UnitTypes::to_color(static_cast<UnitTypes::UnitTypes>(0));
            debug.at<cv::Vec3b>(new_loc[1], new_loc[0])[0] = color[0];
            debug.at<cv::Vec3b>(new_loc[1], new_loc[0])[1] = color[1];
            debug.at<cv::Vec3b>(new_loc[1], new_loc[0])[2] = color[2];
            try
            {
                cv::imshow("Scan", debug);
                cv::waitKey(1);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
#endif
        }
    }
}

void Map::FillMap()
{
    m_debug_map = cv::Mat(m_map_size, m_map_size, CV_8UC3, cv::Scalar(0, 0, 0));
    std::cout << "\nSetting " << m_all_pawns.size() << " pawns on the map.\n";
    for (const auto &pawn : m_all_pawns)
    {

        cv::Vec3i pawn_on_map;
        pawn_on_map[CHANNELS::SIDE] = pawn->GetSide();
        pawn_on_map[CHANNELS::TYPE] = pawn->GetType();
        pawn_on_map[CHANNELS::ID] = pawn->GetId();

        /** @brief Add protection agains pawns that are placed outside the map. */
        if (pawn->GetStartLocation().X() < m_map_size and
            pawn->GetStartLocation().X() >= 0 and
            pawn->GetStartLocation().Y() < m_map_size and
            pawn->GetStartLocation().Y() >= 0)
        {
            m_map.at<cv::Vec3i>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y())) = pawn_on_map;

            auto color = UnitTypes::to_color(pawn->GetType());
            m_debug_map.at<cv::Vec3b>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y()))[0] = color[0];
            m_debug_map.at<cv::Vec3b>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y()))[1] = color[1];
            m_debug_map.at<cv::Vec3b>(cv::Point(pawn->GetStartLocation().X(), pawn->GetStartLocation().Y()))[2] = color[2];
        }
        else
            std::cerr << "\n\n********************\n"
                      << "Warning! loaded pawn start location is not a legal start location! See Resources configurations.\n"
                      << "Please note that map size is: " << m_map_size
                      << "\n\n********************\n";
    }
}
Map::Map(std::list<IUnitMap *> &pawns, int map_size)
    : m_map(cv::Mat(map_size, map_size, CV_32SC3, cv::Scalar(0, 0, 0))),
      m_debug_map(cv::Mat(map_size, map_size, CV_8UC3, cv::Scalar(0, 0, 0))),
      m_all_pawns(pawns),
      m_map_size(map_size)
{
    FillMap();
}

Map::~Map()
{
}