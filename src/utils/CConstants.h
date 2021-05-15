#pragma once
#include <string>
namespace UnitTypes
{
	enum Side
	{
		Defence,
		Offence
	};
	enum UnitTypes
	{
		Airplane = 1,
		Tank = 2,
		Ship = 3,
		AntiAir = 11,
		AntiTank = 12,
		// AntiBoat = 13,
		AntiShip = 13, /** @brief According to the user-story.*/
		Building = 99
	};

	/**
	 * @brief Return char representing a color (0~255)
	 * 
	 * @param unitType 
	 * @return const char 
	 */
	static const char to_color(UnitTypes unitType)
	{
		switch (unitType)
		{
		case UnitTypes::Airplane:
			return 50;
		case UnitTypes::Tank:
			return 80;
		case UnitTypes::Ship:
			return 100;
		case UnitTypes::AntiAir:
			return 130;
		case UnitTypes::AntiTank:
			return 160;
		case UnitTypes::AntiShip:
			return 180;
		case UnitTypes::Building:
			return 200;
		default:
			return 255;
		}
	}
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
