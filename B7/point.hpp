#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
  int x;
  int y;
};

std::ostream& operator<<(std::ostream & os, const Point & point);
std::istream& operator>>(std::istream & sin, Point & point);

#endif
