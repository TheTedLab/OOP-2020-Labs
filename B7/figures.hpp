#ifndef FIGURES_HPP
#define FIGURES_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  using Shape::Shape;
  void draw(std::ostream& os) const override;
};

class Square : public Shape
{
public:
  using Shape::Shape;
  void draw(std::ostream& os) const override;
};

class Triangle : public Shape
{
  using Shape::Shape;
  void draw(std::ostream& os) const override;
};

#endif
