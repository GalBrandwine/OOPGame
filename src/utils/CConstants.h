#pragma once
#include <string>
namespace UnitTypes
{
	enum UnitTypes
	{
		Airplane = 1,
		Tank = 2,
		Ship = 3,
		AntiAir = 11,
		AntiTank = 12,
		// AntiBoat = 13,
		AntiShip = 13, ///<  @brief According to the user-story.
		Building = 99
	};
	static const std::string to_string(UnitTypes unitType)
	{
		switch (unitType)
		{
		case UnitTypes::Airplane:
			return "Airplane";
		case UnitTypes::Tank:
			return "Tank";
		case UnitTypes::Ship:
			return "Ship";
		case UnitTypes::AntiAir:
			return "AntiAir";
		case UnitTypes::AntiTank:
			return "AntiTank";
		case UnitTypes::AntiShip:
			return "AntiShip";
		case UnitTypes::Building:
			return "Building";
		default:
			return "NO SUCH UNITTYPE";
		}
	}
} // namespace UnitTypes
