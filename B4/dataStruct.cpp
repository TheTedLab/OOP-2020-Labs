#include "dataStruct.hpp"
#include <sstream>
#include <stdexcept>

const char DELIMITER = ',';
const int MAX_VALUE = 5;
const int MIN_VALUE = -5;

bool isCorrectKey(const int& key)
{
  return key <= MAX_VALUE && key >= MIN_VALUE;
}

std::istream & inputLine(std::istream & sin)
{
  if (sin.peek() == '\n')
  {
    sin.clear();
    sin.setstate(std::ios_base::failbit);
    return sin;
  }
  while (isspace(sin.peek()))
  {
    sin.ignore(1);
    if (sin.peek() == '\n')
    {
      sin.clear();
      sin.setstate(std::ios_base::failbit);
      return sin;
    }
  }
  return sin;
}

std::istream& operator>>(std::istream& sin, DataStruct& data)
{
  if (sin.peek() == EOF)
  {
    sin.setstate(std::ios_base::failbit);
    return sin;
  }

  sin >> data.key1 >> inputLine;
  if (sin.peek() != DELIMITER || !isCorrectKey(data.key1))
  {
    sin.setstate(std::ios_base::failbit);
    return sin;
  }
  sin.ignore(1);
  
  sin >> inputLine >> data.key2 >> inputLine;
  if (sin.peek() != DELIMITER || !isCorrectKey(data.key2))
  {
    sin.setstate(std::ios_base::failbit);
    return sin;
  }
  sin.ignore(1);

  getline(sin, data.str);
  if (data.str.empty())
  {
    sin.setstate(std::ios_base::failbit);
  }
  
  return sin;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data)
{
  os << data.key1 << DELIMITER << data.key2 << DELIMITER << data.str;
  return os;
}
