#include <list>
#include <string>

#include "CGameAdmin.h"

CGameAdmin::CGameAdmin()
{
	m_reader = new CReader();
	m_unitProperties = new map<int, CUnitProperty *>();

	m_defence = new list<IUnit *>();
	m_attack = new list<IUnit *>();
}

CGameAdmin::~CGameAdmin()
{
	delete m_reader;

	delete m_unitProperties;

	delete m_defence;
	delete m_attack;
	delete m_aux;
}

#pragma region public_functions
int CGameAdmin::LoadGameConfigurations()
{
	bool rc = true;

	list<list<int> *> *properties = new list<list<int> *>();
	list<list<int> *> *attackUnits = new list<list<int> *>();
	list<list<int> *> *defendUnits = new list<list<int> *>();

	if (m_reader->ReadUnitProperties("/home/gal/dev/Game/conf/Resources/UnitsProperties.txt", properties) == 0 ||
		m_reader->ReadUnit("/home/gal/dev/Game/conf/Resources/Attack.txt", attackUnits) == 0 ||
		m_reader->ReadUnit("/home/gal/dev/Game/conf/Resources/Defence.txt", defendUnits) == 0)
	{
		rc = false;
	}

	cout << "---START LOAD UNITS---" << endl;

	LoadUnitProperties(properties);
	/** @note In the given partial implementation, every turn, the properties pointer is passed. 
	 * Another way to pass properties to pawns:
	 * * Properties cant change once they have been loaded, So I could inject them upon units loading time.
	 */
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
	std::list<IUnitMap *> map_pawns;

	/** @todo Add unittest for this case */
	if (m_attack->size() == 0 or m_defence->size() == 0)
	{
		std::cerr << " Cant place on map. Missing pawns \n";
		return 0;
	}

	for (const auto &offence : *m_attack)
	{
		auto casted = dynamic_cast<IUnitMap *>(offence);
		map_pawns.push_back(casted);
	}

	for (const auto &defence : *m_defence)
	{
		auto casted = dynamic_cast<IUnitMap *>(defence);
		map_pawns.push_back(casted);
	}


	std::shared_ptr<IMap> shared_map = std::make_shared<Map>(map_pawns);
	
	/** @brief Inject map to Offence and Defense*/
	for (auto &defence : *m_defence)
	{
		defence->LoadMap(shared_map);
	}
	for (auto &offence : *m_attack)
	{
		offence->LoadMap(shared_map);
	}

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
int CGameAdmin::LoadUnitProperties(list<list<int> *> *properties)
{
	if (properties->size() == 0)
	{
		return 0;
	}

	while (properties->size() > 0)
	{
		list<int> *unitProperties = properties->front();
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
		auto convertedUnitType = static_cast<UnitTypes::UnitTypes>(unit_type);
		cout << " unit type name = " << UnitTypes::to_string(convertedUnitType);

		cout << " speed = " << speed;
		cout << " range = " << range;
		cout << " success probability = " << probability << endl;
		cout << "\n";

		CUnitProperty *up = new CUnitProperty(speed, range, probability);
		m_unitProperties->insert(std::make_pair(unit_type, up));

		delete unitProperties;
	}

	return 1;
}

int CGameAdmin::LoadOffenceUnits(list<list<int> *> *units)
{
	if (units->size() == 0)
	{
		return 0;
	}

	while (units->size() > 0)
	{
		list<int> *unit = units->front();
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

		/**
		 * @todo Adde safety check here:
		 * * Check if data loaded according to game API.
		 * 
		 */
		CLocation start{startLocX, startLocY};
		CLocation target{tarLocX, tarLocY};
		auto convertedUnitType = static_cast<UnitTypes::UnitTypes>(unitType);
		cout << " unit type name = " << UnitTypes::to_string(convertedUnitType);
		cout << "\n";
		IUnit *offence = new COffenceUnit(convertedUnitType, id, start, target, m_aux->GetInstance());
		m_attack->push_back(offence);

		delete unit;
	}

	return 1;
}

int CGameAdmin::LoadDefenceUnits(list<list<int> *> *units)
{
	if (units->size() == 0)
	{
		return 0;
	}

	while (units->size() > 0)
	{
		list<int> *unit = units->front();
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
		CLocation start{startLocX, startLocY};
		/** @todo Add safety checks here. */
		auto convertedUnitType = static_cast<UnitTypes::UnitTypes>(unitType);
		cout << " unit type name = " << UnitTypes::to_string(convertedUnitType);
		cout << "\n";
		IUnit *defence = new CDefenceUnit(convertedUnitType, id, start);
		m_defence->push_back(defence);

		delete unit;
	}

	return 1;
}

int CGameAdmin::IsGameOver()
{
	if (m_attack->size() == 0)
	{
		std::cout << "\nOffence won. YEY!\n";
		return 1;
	}
	else if (m_defence->size() == 0)
	{
		std::cout << "\nDefence won. YEY!\n";
		return 2;
	}

	return 99;
}
#pragma endregion public_functions
