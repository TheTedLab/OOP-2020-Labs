#include "matrix.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

namespace mukhin
{
  Matrix::Matrix():
    rows_(0),
    columns_(0),
    matrix_(nullptr)
  {}

  Matrix::Matrix(const Matrix& matrix):
    rows_(matrix.rows_),
    columns_(matrix.columns_),
    matrix_(new std::shared_ptr<Shape>[matrix.rows_ * matrix.columns_])
  {
    for (size_t i = 0; i < rows_ * columns_; i++)
    {
      matrix_[i] = matrix.matrix_[i];
    }
  }

  Matrix::Matrix(Matrix&& matrix) noexcept:
    rows_(matrix.rows_),
    columns_(matrix.columns_),
    matrix_(std::move(matrix.matrix_))
  {
    matrix.rows_ = 0;
    matrix.columns_ = 0;
    matrix.matrix_.reset();
  }

  Matrix& Matrix::operator=(const Matrix& matrix)
  {
    if (&matrix == this)
    {
      return *this;
    }
    if (rows_ == matrix.rows_ && columns_ == matrix.columns_)
    {
      for (size_t i = 0; i < matrix.rows_ * columns_; i++)
      {
        matrix_[i] = matrix.matrix_[i]; 
      }
    }
    else
    {
      matrixPtr temp(std::make_unique<std::shared_ptr<Shape>[]>(matrix.rows_ * matrix.columns_));
      for (size_t i = 0; i < matrix.rows_ * columns_; i++)
      {
        temp[i] = matrix.matrix_[i];
      }
      rows_ = matrix.rows_;
      columns_ = matrix.columns_;
      matrix_ = std::move(temp);
    }
    return *this;
  }

  Matrix& Matrix::operator=(Matrix&& matrix) noexcept
  {
    if (&matrix == this)
    {
      return *this;
    }
    rows_ = matrix.rows_;
    columns_ = matrix.columns_;
    matrix_ = std::move(matrix.matrix_);
    matrix.rows_ = 0;
    matrix.columns_ = 0;
    matrix.matrix_.reset();
    return *this;
  }

  std::shared_ptr<Shape>& Matrix::getShape(size_t row, size_t column)
  {
    if (row >= rows_ || column >= columns_)
    {
      throw std::invalid_argument("Row and column must be positive numbers, not exceeding "
          + std::to_string(rows_) + " rows and " 
          + std::to_string(columns_) + " columns. Invalid row and column: " 
          + std::to_string(row) + " " + std::to_string(column));
    }
    return matrix_[row * columns_ + column];
  }

  size_t Matrix::getRows() const noexcept
  {
    return rows_;
  }

  size_t Matrix::getColumns() const noexcept
  {
    return columns_;
  }

  void Matrix::addShape(const std::shared_ptr<Shape>& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Invalid shape! Shape is nullptr!");
    }
    if (rows_ == 0 && columns_ == 0)
    {
      rows_ = 1;
      columns_ = 1;
      matrix_ = std::make_unique<std::shared_ptr<Shape>[]>(1);
      matrix_[0] = shape;
    }
    else
    {
      int rowIndex = -1;
      int index = -1;
      for (size_t i = 0; i < rows_; i++)
      {
        if (rowIndex == -1)
        {
          rowIndex = i;
        }
        for (size_t j = i * columns_; j < columns_ * (i + 1); j++)
        {
          if (isShapesOverlayed(shape, matrix_[j]) == true)
          {
            rowIndex = -1;
            index = -1;
            break;
          }
          if (index == -1 && matrix_[j] == nullptr)
          {
            index = j;
          }
        }
      }  
      if (index != -1)
      {
        matrix_[index] = shape;
      }
      else if (rowIndex != -1)
      {
        matrixPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(rows_ * (columns_ + 1));
        for (size_t j = 0; j < rows_; j++)
        {
          for (size_t k = j * columns_; k < columns_ * (j + 1); k++)
          {
            temp[k] = matrix_[k];
          }
        }
        matrix_ = std::move(temp);
        temp = nullptr;
        matrix_[rowIndex * (columns_ + 1) + columns_] = shape;
        ++columns_;
      }
      else
      {
        matrixPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(columns_ * (rows_ + 1));
        for (size_t i = 0; i < rows_ * columns_; i++)
        {
          temp[i] = matrix_[i];
        }
        matrix_ = std::move(temp);
        temp = nullptr;
        matrix_[rows_ * columns_] = shape;
        ++rows_;
      }
    }
  }

  bool Matrix::isShapesOverlayed(const std::shared_ptr<Shape>& shapeOne, const std::shared_ptr<Shape>& shapeTwo)
  {
    if (shapeOne == nullptr || shapeTwo == nullptr)
    {
      return false;
    }
    rectangle_t frameOne = shapeOne->getFrameRect();
    rectangle_t frameTwo = shapeTwo->getFrameRect();
    return ((fabs(frameOne.pos.x - frameTwo.pos.x) < ((frameOne.width / 2) + (frameTwo.width / 2)))
        && (fabs(frameOne.pos.y - frameTwo.pos.y) < ((frameOne.height / 2) + (frameTwo.height / 2))));
  }
}
