#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
 
namespace mukhin
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t& core);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t& core) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    point_t getCore() const noexcept override;
    double getHeight() const noexcept;
    double getWidth() const noexcept;
    double getAngle() const noexcept;
  private:
    point_t pos_;
    double width_;
    double height_;
    double angle_;
  };
}
#endif //RECTANGLE_HPP
