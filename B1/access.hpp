#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <cstdlib>

template <typename Container>
class BracketAccess
{
public:
  using IndexType = size_t;
  using ElementType = typename Container::reference;
  static IndexType begin(const Container &)
  {
    return 0;
  }

  static IndexType end(const Container & cont)
  {
    return cont.size();
  }

  static ElementType getElement(Container & cont, IndexType index)
  {
    return cont[index];
  }

  static IndexType next(IndexType index)
  {
    return ++index;
  }
};

template <typename Container>
class AtAccess
{
public:
  using IndexType = size_t;
  using ElementType = typename Container::reference;
  static IndexType begin(const Container &)
  {
    return 0;
  }

  static IndexType end(const Container & cont)
  {
    return cont.size();
  }

  static ElementType getElement(Container & cont, IndexType index)
  {
    return cont.at(index);
  }

  static IndexType next(IndexType index)
  {
    return ++index;
  }
};

template <typename Container>
class IteratorAccess
{
public:
  using Iterator = typename Container::iterator;
  using ElementType = typename Container::reference;
  static Iterator begin(Container & cont)
  {
    return cont.begin();
  }

  static Iterator end(Container & cont)
  {
    return cont.end();
  }

  static ElementType getElement(Container &, Iterator & iter)
  {
    return *iter;
  }

  static Iterator next(Iterator iter)
  {
    return ++iter;
  }
};

#endif
