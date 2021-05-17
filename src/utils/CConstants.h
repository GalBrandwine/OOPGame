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
	static const std::array<char, 3> to_color(UnitTypes unitType)
	{
		std::array<char, 3> color;
		switch (unitType)
		{
		case UnitTypes::Airplane:
			color[0] = 50;
			color[1] = 100;
			color[2] = 255;
			return color;
		case UnitTypes::Tank:
			color[0] = 80;
			color[1] = 80;
			color[2] = 255;
			return color;
		case UnitTypes::Ship:
			color[0] = 100;
			color[1] = 100;
			color[2] = 255;
			return color;
		case UnitTypes::AntiAir:
			color[0] = 100;
			color[1] = 100;
			color[2] = 0;
			return color;
		case UnitTypes::AntiTank:
			color[0] = 100;
			color[1] = 255;
			color[2] = 0;
			return color;
		case UnitTypes::AntiShip:
			color[0] = 50;
			color[1] = 255;
			color[2] = 0;
			return color;
		case UnitTypes::Building:
			color[0] = 0;
			color[1] = 255;
			color[2] = 0;
			return color;
		default:
			color[0] = 255;
			color[1] = 255;
			color[2] = 255;
			return color;
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
