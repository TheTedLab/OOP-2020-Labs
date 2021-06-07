#ifndef TASK_ONE_HPP
#define TASK_ONE_HPP

#include <vector>
#include <list>
#include "show.hpp"
#include "sort.hpp"
#include "access.hpp"

void task_1(const char * direction)
{
  std::function<bool(int, int)> compare = getCompare<int>(direction);
  std::vector<int> input_vector;

  int data = 0;
  while (std::cin >> data)
  {
    input_vector.push_back(data);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Invalid input! Not an integer value!\n");
  }

  if (input_vector.empty())
  {
    return;
  }

  std::vector<int> bracket_vector = input_vector;
  sort<BracketAccess>(bracket_vector, compare);
  show(bracket_vector);

  std::vector<int> at_vector = input_vector;
  sort<AtAccess>(at_vector, compare);
  show(at_vector);

  std::list<int> list(input_vector.begin(), input_vector.end());
  sort<IteratorAccess>(list, compare);
  show(list); 
}

#endif
