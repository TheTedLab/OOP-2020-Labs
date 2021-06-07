#ifndef TASK_FOUR_HPP
#define TASK_FOUR_HPP

#include <random>
#include <cstdlib> 
#include <vector>
#include "show.hpp"
#include "sort.hpp"

void fillRandom(double * array, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Invalid size of array! Size must be positive!\n");
  }

  if (array == nullptr)
  {
    throw std::invalid_argument("Pointer mustn't be nullptr!\n");
  }

  std::default_random_engine gen;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(gen);
  }
}

void task_4(const char * direction, int size)
{
  std::function<bool(double, double)> compare = getCompare<double>(direction);

  if (size <= 0)
  {
    throw std::invalid_argument("Invalid size of array! Size mustn't be negative!\n");
  }

  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  show(vector);
  sort<IteratorAccess>(vector, compare);
  show(vector);
}

#endif
