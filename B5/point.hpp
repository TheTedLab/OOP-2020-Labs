#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
  int x;
  int y;
};

std::istream& skipBlanks(std::istream& in);
std::istream& operator>>(std::istream& in, Point & point);
std::ostream& operator<<(std::ostream& os, const Point & point);

#endif
