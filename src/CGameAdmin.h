#pragma once
#include <iostream>
#include <map>

#include "CDefenceUnit.h"
#include "COffenceUnit.h"
#include "CReader.h"
#include "CUnitProperty.h"

using namespace std;

class CGameAdmin
{
public:
	CGameAdmin();
	~CGameAdmin();

public:
	int LoadGameConfigurations();

	int PlaceOnMap();
	int Play();

private:

	/**
	 * @brief I prefere smart pointers.
	 * They much measier to handle, and have almost to nothing CPU overhead.
	 * 
	 * int LoadUnitProperties(list <list<int>*>* properties);
	 * int LoadOffenceUnits(list <list<int>*>* units);
	 * int LoadDefenceUnits(list <list<int>*>* units);
	 */
	int LoadUnitProperties(list<list<int> *> *properties);
	int LoadOffenceUnits(list<list<int> *> *units);
	int LoadDefenceUnits(list<list<int> *> *units);
	int IsGameOver();

private:
	CReader *m_reader = nullptr;

	map<int, CUnitProperty *> *m_unitProperties = nullptr;
	list<COffenceUnit *> *m_attack = nullptr;
	list<CDefenceUnit *> *m_defence = nullptr;
};
