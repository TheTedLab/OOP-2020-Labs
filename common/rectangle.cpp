#include "rectangle.hpp"
#include <stdexcept>
#include <string>
#include <cmath>
 
namespace mukhin
{
  const double CIRCLE_ANGLE = 360.0;

  Rectangle::Rectangle(const double width, const double height, const point_t& core) :
    pos_(core),
    width_(width),
    height_(height),
    angle_(0)
  {
    if (height <= 0 || width <= 0)
    {
      throw std::invalid_argument(std::string("Height and width must be positive numbers! Height:"
          + std::to_string(height) + " Width: "
          + std::to_string(width)));
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double angleRadian = angle_ * M_PI / (CIRCLE_ANGLE / 2); 
    return { pos_, width_ * fabs(cos(angleRadian)) + height_ * fabs(sin(angleRadian)),
        height_ * fabs(cos(angleRadian)) + width_ * fabs(sin(angleRadian)) };

  }

  void Rectangle::move(const double dx, const double dy) noexcept
  {
    pos_.x += dx;
    pos_.y += dy;
  }
 
  void Rectangle::move(const point_t& core) noexcept
  {
    pos_ = core;
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument(std::string("Factor must be a positive number! Factor: "
          + std::to_string(factor)));
    }
    height_ *= factor;
    width_ *= factor;
  }

  void Rectangle::rotate(const double angle) noexcept
  {
    angle_ += angle;
    angle_ = (angle_ < 0.0) ? CIRCLE_ANGLE + fmod(angle_, CIRCLE_ANGLE) : fmod(angle_, CIRCLE_ANGLE);
  }

  point_t Rectangle::getCore() const noexcept
  {
    return pos_;
  }

  double Rectangle::getHeight() const noexcept
  {
    return height_;
  }

  double Rectangle::getWidth() const noexcept
  {
    return width_;
  }

  double Rectangle::getAngle() const noexcept
  {
    return angle_;
  }
}
