#ifndef SHOW_HPP
#define SHOW_HPP

#include <list>
#include <iostream>

template <typename T>
void show(typename std::list<T>::iterator iter_begin, typename std::list<T>::iterator iter_end, std::ostream & os)
{
  while (iter_begin != iter_end)
  {
    os << *iter_begin << ' ';
    iter_begin++;
    if (iter_begin == iter_end)
    {
      break;
    }
    iter_end--;
    os << *iter_end << ' ';
  }
  os << '\n';
}

#endif
