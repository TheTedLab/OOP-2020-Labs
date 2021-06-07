#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace mukhin
{
  class Circle : public Shape
  {
  public:
    Circle(const double radius, const point_t& core);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t& core) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    point_t getCore() const noexcept override;
    double getRadius() const noexcept;
  private:
    double radius_;
    point_t pos_;
  };
}
#endif //CIRCLE_HPP
