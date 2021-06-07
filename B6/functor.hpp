#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <limits>
#include <iostream>

class Functor
{
public:
  Functor();
  void operator()(int);
  friend std::ostream & operator<<(std::ostream & os, const Functor & func);

private:
  int maxValue_;
  int minValue_;
  int positive_;
  int negative_;
  int amount_;
  int first_;
  long long sumOfOdd_;
  long long sumOfEven_;
  bool isEqual;
};

#endif
