#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const double radius, const point_t& core);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t& core) override;
  point_t getCore() const;
  double getRadius() const;
private:
  double radius_;
  point_t pos_;
};
#endif //CIRCLE_HPP
