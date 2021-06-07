#include "point.hpp"
#include "utils.hpp"
#include "istreamGuard.hpp"

std::ostream& operator<<(std::ostream& os, const Point& point)
{
  os << '(' << point.x << ';' << point.y << ')';
  return os;
}

std::istream& operator>>(std::istream& sin, Point& point)
{
  IstreamGuard istreamGuard(sin);
  sin.unsetf(std::ios::skipws);

  sin >> skipBlanks;
  if (sin.get() != '(')
  {
    sin.setstate(std::ios::failbit);
  }

  sin >> skipBlanks >> point.x >> skipBlanks;
  if (sin.get() != ';')
  {
    sin.setstate(std::ios::failbit);
  }

  sin >> skipBlanks >> point.y >> skipBlanks;
  if (sin.get() != ')')
  {
    sin.setstate(std::ios::failbit);
  }
  return sin;
}
