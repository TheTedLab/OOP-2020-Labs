#include "circle.hpp"
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

Circle::Circle(const double radius, const point_t& core):
  radius_(radius),
  pos_(core)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Wrong radius!");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { pos_, 2 * radius_, 2 * radius_ };
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t& core)
{
  pos_ = core;
}

point_t Circle::getCore() const
{
  return pos_;
}

double Circle::getRadius() const
{
  return radius_;
}
