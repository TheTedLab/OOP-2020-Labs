#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

const auto Comparator = [](const DataStruct& lhs, const DataStruct& rhs) -> bool
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }

  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }

  return lhs.str.size() < rhs.str.size();
};
 
void task()
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)), (std::istream_iterator<DataStruct>()));

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Error while reading data in task!\n");
  }

  std::sort(vector.begin(), vector.end(), Comparator);
  std::ostream_iterator<DataStruct> out_iter(std::cout, "\n");
  std::copy(vector.begin(), vector.end(), out_iter);
}

#endif
