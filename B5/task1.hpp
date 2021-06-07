#ifndef TASK_ONE_HPP
#define TASK_ONE_HPP

#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>

using in_iter = std::istream_iterator<std::string>;
using out_iter = std::ostream_iterator<std::string>;

void task1(std::istream& sin, std::ostream& os)
{
  std::unordered_set<std::string> list{in_iter(sin), in_iter()};

  if (!sin.eof() && sin.fail())
  {
    throw std::invalid_argument("Error while reading data in task1!\n");
  }

  std::copy(list.begin(), list.end(), out_iter(os, "\n"));
}

#endif
