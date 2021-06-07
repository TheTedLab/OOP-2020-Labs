#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace mukhin
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const size_t size);
    CompositeShape(const CompositeShape &shapes);
    CompositeShape(CompositeShape &&shapes) noexcept;
    std::shared_ptr<Shape> operator[](size_t index) const;
    CompositeShape &operator=(const CompositeShape &shapes);
    CompositeShape &operator=(CompositeShape &&shapes) noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    point_t getCore() const noexcept override;
    void move(const double x, const double y) noexcept override;
    void move(const point_t& core) noexcept override;
    void scale(const double factor) override;
    void addShape(const std::shared_ptr<Shape> &shape);
    void deleteShape(const size_t index);
    void rotate(const double angle) noexcept override;
    Matrix getMatrixLayer();
    size_t getSize() const noexcept;
    size_t getSpace() const noexcept;
  private:
    using shapePtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t size_;
    size_t space_;
    shapePtr shapes_;
  };
}
#endif //COMPOSITE_SHAPE_HPP
