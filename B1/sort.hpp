#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <vector>
#include <string>
#include "access.hpp"

template <typename T>
std::function<bool(T, T)> getCompare(std::string direction)
{
  if (direction == "ascending")
  {
    return std::greater<const T>();
  }
  else if (direction == "descending")
  {
    return std::less<const T>();
  }
  else
  {
    throw std::invalid_argument("Invalid sort type!\n");
  }
}

template <template <typename> class AccessType, typename Container>
void sort(Container & cont, std::function<bool(typename Container::value_type, typename Container::value_type)> compare)
{
  typedef AccessType<Container> Access;
  const auto begin = Access::begin(cont);
  const auto end = Access::end(cont);

  for (auto i = begin; i != end; i = Access::next(i))
  {
    for (auto j = Access::next(i); j != end; j = Access::next(j))
    {
      if (compare(Access::getElement(cont, i), Access::getElement(cont, j)))
      {
        std::swap(Access::getElement(cont, i), Access::getElement(cont, j));
      }
    }
  }
}

#endif
