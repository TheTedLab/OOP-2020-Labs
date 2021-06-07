#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const double width, const double height, const point_t& core): 
  pos_(core),
  width_(width),
  height_(height)
{
  if (height <= 0 || width <= 0)
  {
    throw std::invalid_argument("Wrong height or width!");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { pos_, width_, height_ };
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::move(const point_t& core)
{
  pos_ = core;
}

point_t Rectangle::getCore() const
{
  return pos_;
}

double Rectangle::getHeight() const
{
  return height_;
}

double Rectangle::getWidth() const
{
  return width_;
}
