#ifndef TASK_HPP
#define TASK_HPP

#include <algorithm>
#include <functional>
#include "functor.hpp"
#include "inputIterator.hpp"

void task(const int lineLength, std::istream& in, std::ostream& os)
{
  Functor functor(os, lineLength);
  std::for_each(InputIterator(in), InputIterator(), std::ref(functor));
}

#endif
