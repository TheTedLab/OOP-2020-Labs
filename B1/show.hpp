#ifndef SHOW_HPP
#define SHOW_HPP

#include <iostream>
#include <iterator>

template <typename T>
void show(const T& container, const char * delimiter = " ")
{
  std::ostream_iterator<typename T::value_type> out_iter(std::cout, delimiter);
  std::copy(container.begin(), container.end(), out_iter);
  std::cout << '\n';
}

#endif
