#ifndef TASK_TWO_HPP
#define TASK_TWO_HPP

#include <iostream>
#include <algorithm>
#include "factorial.hpp"

void task_2()
{
  std::ostream_iterator<int> out_iter(std::cout, " ");

  Factorial factorial;
  std::copy(factorial.begin(), factorial.end(), out_iter);
  std::cout << '\n';

  std::reverse_copy(factorial.begin(), factorial.end(), out_iter);
  std::cout << '\n';
}

#endif
