#ifndef TASK_TWO_HPP
#define TASK_TWO_HPP

#include <list>
#include <iostream>
#include <stdexcept>
#include "show.hpp"

void task_2()
{
  std::list<int> list;
  int value = 0;
  while (std::cin >> value)
  {
    if (value < 1 || value > 20)
    {
      throw std::invalid_argument("Value must be between 1 and 20!\n");
    }

    if (list.size() >= 20)
    {
      throw std::invalid_argument("List size must be less or equal to 20 elements!\n");
    }

    list.push_back(value);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task_2!\n");
  }

  show<int>(list.begin(), list.end(), std::cout);
}

#endif
