#include "utils.hpp"
#include <cctype>

std::istream& skipBlanks(std::istream& sin)
{
  while (!sin.eof() && std::isblank(sin.peek()))
  {
    sin.ignore();
  }
  return sin;
}
