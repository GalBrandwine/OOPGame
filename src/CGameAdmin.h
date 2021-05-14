#pragma once
#include <iostream>
#include <map>

#include "utils/CConstants.h"
#include "CDefenceUnit.hpp"
#include "COffenceUnit.hpp"
#include "CReader.h"
#include "CUnitProperty.hpp"
#include "Map.hpp"
/**
 * @brief I dont like using STD namespace
 * using namespace std;
 */

class CGameAdmin
{
public:
	CGameAdmin();
	~CGameAdmin();

public:
	int LoadGameConfigurations();
	/**
	 * @brief Place pawns and building on map given loaded presettings.
	 * 
	 * @return int 
	 */
	int PlaceOnMap();
	int Play();

private:
	int LoadUnitProperties(list<list<int> *> *properties);
	int LoadOffenceUnits(list<list<int> *> *units);
	int LoadDefenceUnits(list<list<int> *> *units);

	/**
	 * @brief The game ends when there are no Offense units.
	 * 
	 * @note This termination term is unfair. What will happen when there are no more Defence units? the game will continue forever?
	 * 
	 * **Addition**
	 * * Possible return values:
	 *   * 1 - No more Offence units - Hence Defence won.
	 *   * 2 - No more Defence units - Hence Offence won.
	 *   * 99 - Un expected game ending - this should be catched and logged.
	 * @return int
	 */
	int IsGameOver();

private:
	CReader *m_reader = nullptr;

	map<int, CUnitProperty *> *m_unitProperties = nullptr;
	list<IUnit *> *m_attack = nullptr;
	list<IUnit *> *m_defence = nullptr;
};
