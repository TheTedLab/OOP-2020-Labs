#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const double width, const double height, const point_t& core);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t& core) override;
  point_t getCore() const;
  double getHeight() const;
  double getWidth() const;
private:
  point_t pos_;
  double width_;
  double height_;
};
#endif //RECTANGLE_HPP
