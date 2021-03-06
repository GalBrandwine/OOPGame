#include <list>
#include <string>

#include "CGameAdmin.h"

bool isAliveHelper(IUnit *unit)
{
	auto is_alive = unit->IsAlive();
	if (!is_alive)
	{
		delete (unit);
		return true;
	}

	return false;
}
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

	for (auto &property : *m_unitProperties)
	{
		delete property.second;
	}
	m_unitProperties->clear();
	delete m_unitProperties;

	while (m_mapPawns.size() > 0)
	{
		auto pawn = m_mapPawns.front();
		delete pawn;
		m_mapPawns.pop_front();
	}

	while (m_attack->size() > 0)
	{
		auto attacker = m_attack->front();
		delete attacker;
		m_attack->pop_front();
	}

	while (m_defence->size() > 0)
	{
		auto defender = m_defence->front();
		delete defender;
		m_defence->pop_front();
	}

	delete m_defence;
	delete m_attack;
}

#pragma region public_functions
int CGameAdmin::LoadGameConfigurations()
{
	bool rc = true;

	list<list<int> *> *properties = new list<list<int> *>();
	list<list<int> *> *attackUnits = new list<list<int> *>();
	list<list<int> *> *defendUnits = new list<list<int> *>();

	if (m_reader->ReadUnitProperties("../conf/Resources/UnitsProperties.txt", properties) == 0 ||
		m_reader->ReadUnit("../conf/Resources/Attack.txt", attackUnits) == 0 ||
		m_reader->ReadUnit("../conf/Resources/Defence.txt", defendUnits) == 0)
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

	/** @todo Add unittest for this case */
	if (m_attack->size() == 0 or m_defence->size() == 0)
	{
		std::cerr << " Cant place on map. Missing pawns \n";
		return 0;
	}

	for (const auto &offence : *m_attack)
	{
		auto casted = dynamic_cast<IUnitMap *>(offence);
		m_mapPawns.push_back(casted);
	}

	for (const auto &defence : *m_defence)
	{
		auto casted = dynamic_cast<IUnitMap *>(defence);
		m_mapPawns.push_back(casted);
	}

	std::shared_ptr<IMap> shared_map = std::make_shared<Map>(m_mapPawns, MAP_SIZE);

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

	while (IsGameOver() != 1 and turnNumber < MAXIMUM_GAME_LENGTH)
	{
		/** @brief Perform actions */
		for (auto offenceIterator = m_attack->begin(); offenceIterator != m_attack->end(); ++offenceIterator)
		{
			(*offenceIterator)->PerformTurn(m_unitProperties);
		}

		for (auto defenceIterator = m_defence->begin(); defenceIterator != m_defence->end(); ++defenceIterator)
		{
			(*defenceIterator)->PerformTurn(m_unitProperties);
		}

		/** @brief Maintain Players */
		m_attack->remove_if(isAliveHelper);
		m_defence->remove_if(isAliveHelper);

		cout << "Turn #: " << turnNumber++ << endl;
	}

	if (!IsGameOver())
	{
		std::cout << "\n***************\n\n"
				  << "\n*************** No one won! ***************\n"
				  << "\n***************\n\n";
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

		CUnitProperty *up = new CUnitProperty(range, probability, speed);
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
		IUnit *defence = new CDefenceUnit(convertedUnitType, id, start, m_aux->GetInstance());
		m_defence->push_back(defence);

		delete unit;
	}

	return 1;
}

int CGameAdmin::IsGameOver()
{
	if (m_attack->size() == 0)
	{
		std::cout << "\n\n***************************\n"
				  << "Defence won. YEY!\n"
				  << "\n\n***************************\n";
		return 1;
	}
	else if (m_defence->size() == 0)
	{
		std::cout << "\n\n***************************\n"
				  << "Offence won. YEY!\n"
				  << "\n\n***************************\n";
		return 2;
	}

	return 99;
}
#pragma endregion public_functions
