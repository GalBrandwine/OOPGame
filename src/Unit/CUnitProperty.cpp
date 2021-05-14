#include "CUnitProperty.hpp"

const int CUnitProperty::GetSpeed() const
{
  return m_speed;
}

const int CUnitProperty::GetHitRange() const
{
  return m_hitRange;
}

const int CUnitProperty::GetProbability() const
{
  return m_hitProbability;
}

CUnitProperty::CUnitProperty(int range, int probability, int speed)
    : m_speed(speed),
      m_hitRange(range),
      m_hitProbability(probability)
{
}

CUnitProperty::CUnitProperty(int range, int probability)
    : m_hitRange(range),
      m_hitProbability(probability)
{
}

CUnitProperty::~CUnitProperty()
{
}