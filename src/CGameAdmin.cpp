#include <list>
#include <string>

#include "CGameAdmin.h"


CGameAdmin::CGameAdmin()
{
	m_reader = new CReader();
	
	m_unitProperties = new map<int, CUnitProperty*>();

	m_defence = new list<CDefenceUnit*>();
	m_attack = new list<COffenceUnit*>();
}

CGameAdmin::~CGameAdmin()
{
	delete m_reader;

	delete m_unitProperties;

	delete m_defence;
	delete m_attack;
}

#pragma region public_functions
int CGameAdmin::LoadGameConfigurations()
{
	bool rc = true;

	list<list<int>*>* properties = new list<list<int>*>();
	list<list<int>*>* attackUnits = new list<list<int>*>();
	list<list<int>*>* defendUnits = new list<list<int>*>();

	if (m_reader->ReadUnitProperties(".\\Resources\\UnitsProperties.txt", properties) == 0 ||
		m_reader->ReadUnit(".\\Resources\\Attack.txt", attackUnits) == 0 ||
		m_reader->ReadUnit(".\\Resources\\Defence.txt", defendUnits) == 0)
	{
		rc = false;
	}

	cout << "---START LOAD UNITS---" << endl;
	
	LoadUnitProperties(properties);
	LoadOffenceUnits(attackUnits);
	LoadDefenceUnits(defendUnits);
	
	cout << "---STOP LOAD UNITS---" << endl;

	delete properties;
	delete attackUnits;
	delete defendUnits;

	return rc;
}

int CGameAdmin::PlaceOnMap()
{
	//TODO. Add your code here.

	return 1;
}

int CGameAdmin::Play()
{
	int turnNumber = 0;

	while (IsGameOver() != 1)
	{
		for (auto offenceIterator = m_attack->begin(); offenceIterator != m_attack->end(); ++offenceIterator)
		{
			(*offenceIterator)->PerformTurn(m_unitProperties);
		}

		for (auto defenceIterator = m_defence->begin(); defenceIterator != m_defence->end(); ++defenceIterator)
		{
			(*defenceIterator)->PerformTurn(m_unitProperties);
		}

		cout << "Turn #: " << turnNumber++ << endl;
	}

	return 1;
}
#pragma endregion public_functions

#pragma region private_functions
int CGameAdmin::LoadUnitProperties(list<list<int>*>* properties)
{
	if (properties->size() == 0)
	{
		return 0;
	}

	while (properties->size() > 0)
	{
		list<int>* unitProperties = properties->front();
		properties->pop_front();

		int unit_type = unitProperties->front();
		unitProperties->pop_front();

		int speed = 0;
		if (unitProperties->size() > 2)
		{
			speed = unitProperties->front();
			unitProperties->pop_front();
		}

		int range = unitProperties->front();
		unitProperties->pop_front();

		int probability = unitProperties->front();
		unitProperties->pop_front();

		cout << "unit type = " << unit_type;
		cout << " speed = " << speed;
		cout << " range = " << range;
		cout << " success probability = " << probability << endl;

		CUnitProperty* up = new CUnitProperty(speed, range, probability);
		m_unitProperties->insert(make_pair(unit_type, up));

		delete unitProperties;
	}

	return 1;
}

int CGameAdmin::LoadOffenceUnits(list <list<int>*>* units)
{
	if (units->size() == 0)
	{
		return 0;
	}

	while (units->size() > 0)
	{
		list<int>* unit = units->front();
		units->pop_front();

		int unitType = unit->front();
		unit->pop_front();

		int id = unit->front();
		unit->pop_front();

		int startLocX = unit->front();
		unit->pop_front();

		int startLocY = unit->front();
		unit->pop_front();

		int tarLocX = unit->front();
		unit->pop_front();

		int tarLocY = unit->front();
		unit->pop_front();

		cout << "unit type = " << unitType;
		cout << " id = " << id;
		cout << " start loc x = " << startLocX;
		cout << " start loc y = " << startLocY;
		cout << " tar loc x = " << tarLocX;
		cout << " tar loc y = " << tarLocY << endl;

		//TODO. Add your code here
		m_attack->push_back(unit);

		delete unit;
	}

	return 1;
}

int CGameAdmin::LoadDefenceUnits(list <list<int>*>* units)
{
	if (units->size() == 0)
	{
		return 0;
	}

	while (units->size() > 0)
	{
		list<int>* unit = units->front();
		units->pop_front();

		int unitType = unit->front();
		unit->pop_front();

		int id = unit->front();
		unit->pop_front();

		int startLocX = unit->front();
		unit->pop_front();

		int startLocY = unit->front();
		unit->pop_front();

		cout << "unit type = " << unitType;
		cout << " id = " << id;
		cout << " start loc x = " << startLocX;
		cout << " start loc y = " << startLocY << endl;

		//TODO. Add your code here
		m_defence->push_back(unit);

		delete unit;
	}

	return 1;
}

int CGameAdmin::IsGameOver()
{
	//TODO. Add your code here

	return 1;
}
#pragma endregion public_functions
