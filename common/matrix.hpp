#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace mukhin
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) noexcept;
    std::shared_ptr<Shape>& getShape(size_t row, size_t column);
    size_t getRows() const noexcept;
    size_t getColumns() const noexcept;
    void addShape(const std::shared_ptr<Shape>& shape);
  private:
    using matrixPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t rows_;
    size_t columns_;
    matrixPtr matrix_;
    bool isShapesOverlayed(const std::shared_ptr<Shape>& shapeOne, const std::shared_ptr<Shape>& shapeTwo);
  };
}

#endif
