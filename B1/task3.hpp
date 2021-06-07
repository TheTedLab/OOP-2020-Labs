#ifndef TASK_THREE_HPP
#define TASK_THREE_HPP

#include <iostream>
#include <vector>
#include "show.hpp"

void task_3()
{
  std::vector<int> input_vector;
  int value = 0;

  while (std::cin >> value)
  {
    if (value == 0)
    {
      break;
    }
    input_vector.push_back(value);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Invalid input! Not an integer value!\n");
  }
  if (value != 0)
  {
    throw std::invalid_argument("Invalid input! Last value not 0!\n");
  }
  if (input_vector.empty())
  {
    return;
  }
    
  auto last_value = input_vector.back();
  switch(last_value)
  {
  case 1:
    for (auto it = input_vector.begin(); it != input_vector.end();)
    {
      if (*it % 2 == 0)
      {
        it = input_vector.erase(it);
      }
      else
      {
        it++;
      }
    }
    break;
  case 2:
    for (auto it = input_vector.begin(); it != input_vector.end();)
    {
      if (*it % 3 == 0)
      {
        it = input_vector.insert(it + 1, 3, 1);
        it+=3;
      }
      else
      {
        it++;
      }
    }
    break;
  }
  show(input_vector);
}

#endif
