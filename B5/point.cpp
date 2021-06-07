#include "point.hpp"
#include <cctype>

std::istream& skipBlanks(std::istream& in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}

std::istream& operator>>(std::istream& in, Point& point)
{
  char letter = '\0';
  in >> skipBlanks >> letter;

  if (in.peek() == EOF)
  {
    throw std::invalid_argument("Invalid format!\n");
  }

  if (letter != '(')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  in >> skipBlanks >> point.x >> skipBlanks >> letter;
  if (letter != ';')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  in >> skipBlanks >> point.y >> skipBlanks >> letter;
  if (letter != ')')
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
  os << " (" << point.x << "; " << point.y << ')';
  return os;
}
