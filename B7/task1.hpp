#ifndef TASK_ONE_HPP
#define TASK_ONE_HPP

#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <cmath>

using in_iter = std::istream_iterator<double>;
using out_iter = std::ostream_iterator<double>;

void task1(std::istream & sin, std::ostream & os)
{
  auto functor = std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1);
  std::transform(in_iter(sin), in_iter(), out_iter(os, "\n"), functor);
  if (!sin.eof() && sin.fail())
  {
    throw std::ios::failure("Error while reading data in task1!\n");
  }
}

#endif
