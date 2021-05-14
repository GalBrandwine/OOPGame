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

std::ostream &operator<<(std::ostream &o, CUnitProperty const &unitP)
{
    return o << "Hit range: " << unitP.m_hitRange
             << "\n"
             << "Speed: " << unitP.m_speed
             << "\n"
             << "Hit probability: " << unitP.m_hitProbability;
}