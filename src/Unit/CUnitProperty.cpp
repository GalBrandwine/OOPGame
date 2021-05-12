#include "CUnitProperty.hpp"
CUnitProperty::CUnitProperty(int range, int probability, int speed)
    : Speed(speed),
      Range(range),
      Probability(probability)
{
}

CUnitProperty::CUnitProperty(int range, int probability)
    : Range(range),
      Probability(probability)
{
}

CUnitProperty::~CUnitProperty()
{
}