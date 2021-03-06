#pragma once
#include "CLocation.h"
#include <math.h>
/**
 * @brief Im not sure what this CAuxiliary creature is.
 * * *It looks like a singeltone, that acts like a factory. But why?*
 * 
 */
class CAuxiliary
{
public:
	static CAuxiliary *GetInstance();

	/**
	 * @brief Get the Direction object
	 * 
  	 * \f$
	 * \text{direction} = [destLocationX - currentLocationX, destLocationY - currentLocationY]  \\
	 * \text{|direction|} = \sqrt{(directionX)^2+(directionY)^2}								\\
	 * \text{directionUnit} = \frac{\text{direction}}{\text{|direction|} }
	 * \f$.
	 * 
	 * @param[in] currLocation 
	 * @param[in] destLocation 
	 * @param[out] direction Cdirection * a unit vector with direction to target
	 */
	const void GetDirection(const CLocation *currLocation, const CLocation *destLocation, Cdirection *direction);
	static int TryHitOpponent(int probability);

	/**
	 * @brief Move unit inside map parimiters
	 * 
	 * @param currLocation 
	 * @param destLocation 
	 * @param directionOnX 
	 * @param directionOnY 
	 * @param speed 
	 * @param boundaries 
	 */
	static void MoveUnit(CLocation *currLocation, CLocation *destLocation, int directionOnX, int directionOnY, int speed, int boundaries);

private:
	CAuxiliary();
	~CAuxiliary() { delete m_instance; };
	static CAuxiliary *m_instance;
};
