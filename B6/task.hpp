#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <algorithm>
#include <iterator>
#include "functor.hpp"

using in_iter = std::istream_iterator<int>;

void task(std::istream & sin, std::ostream & os)
{
  Functor func = std::for_each(in_iter(sin), in_iter(), Functor());

  if (!sin.eof() && sin.fail())
  {
    throw std::ios_base::failure("Error while reading data in task!\n");
  }

  os << func;
}

#endif
