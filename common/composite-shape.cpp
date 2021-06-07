#include "composite-shape.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

namespace mukhin
{
  const double CIRCLE_ANGLE = 360.0;

  CompositeShape::CompositeShape() noexcept:
    size_(0),
    space_(0),
    shapes_(nullptr)
  {}

  CompositeShape::CompositeShape(const size_t space):
    size_(0),
    space_(space),
    shapes_(new std::shared_ptr<Shape>[space_])
  {}

  CompositeShape::CompositeShape(const CompositeShape &shapes):
    size_(shapes.size_),
    space_(shapes.space_),
    shapes_(new std::shared_ptr<Shape>[shapes.space_])
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = shapes.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape &&shapes) noexcept:
    size_(shapes.size_),
    space_(shapes.space_),
    shapes_(std::move(shapes.shapes_))
  {
    shapes.size_ = 0;
    shapes.shapes_.reset();
    shapes.space_ = 0;
  }

  std::shared_ptr<Shape> CompositeShape::operator[](size_t index) const
  {
    if (size_ == 0 || index > (size_ - 1))
    {
      throw std::out_of_range("Index out of range! Invalid index: "
          + std::to_string(index));
    }
    return shapes_[index];
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape &shapes)
  {
    if (&shapes == this)
    {
      return *this;
    }
    shapePtr temp(new std::shared_ptr<Shape>[shapes.space_]);
    for (size_t i = 0; i < shapes.size_; i++)
    {
      temp[i] = shapes.shapes_[i];
    }
    size_ = shapes.size_;
    space_ = shapes.space_;
    shapes_ = std::move(temp);
    return *this;
  }
    
  CompositeShape& CompositeShape::operator=(CompositeShape &&shapes) noexcept
  {
    if (&shapes == this)
    {
      return *this;
    }
    size_ = shapes.size_;
    space_ = shapes.space_;
    shapes_ = std::move(shapes.shapes_);
    shapes.size_ = 0;
    shapes.space_ = 0;
    shapes.shapes_.reset();
    return *this; 
  }

  double CompositeShape::getArea() const noexcept
  {
    double commonArea = 0.0;
    for (size_t i = 0; i < size_; i++)
    {
      commonArea += shapes_[i]->getArea();
    }
    return commonArea;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return rectangle_t{{0, 0}, 0, 0};
    }
    rectangle_t frameRect = shapes_[0]->getFrameRect();
    double top = frameRect.pos.y + frameRect.height / 2;
    double bottom = frameRect.pos.y - frameRect.height / 2;
    double right = frameRect.pos.x + frameRect.width / 2;
    double left = frameRect.pos.x - frameRect.width / 2;
    for (size_t i = 0; i < size_; i++)
    {
      frameRect = shapes_[i]->getFrameRect();
      top = std::max(frameRect.pos.y + frameRect.height / 2, top);
      bottom = std::min(frameRect.pos.y - frameRect.height / 2, bottom);
      right = std::max(frameRect.pos.x + frameRect.width / 2, right);
      left = std::min(frameRect.pos.x - frameRect.width / 2, left);
    }
    return { {(left + (right - left) / 2), (bottom + (top - bottom) / 2)}, (right - left), (top - bottom)};
  }

  point_t CompositeShape::getCore() const noexcept
  {
    return getFrameRect().pos;
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::move(const point_t& core) noexcept
  {
    double diffX = core.x - getFrameRect().pos.x;
    double diffY = core.y - getFrameRect().pos.y;
    move(diffX, diffY);
  }

  void CompositeShape::scale(const double factor)
  {
    if (factor <= 0.0)
    {
      throw std::invalid_argument("Factor must be a positive number! Invalid factor: " 
          + std::to_string(factor));
    }
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(factor);
      double diffX = shapes_[i]->getCore().x - getFrameRect().pos.x;
      double diffY = shapes_[i]->getCore().y - getFrameRect().pos.y;
      shapes_[i]->move(diffX * (factor - 1), diffY * (factor - 1));
    }
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Invalid shape! Shape is nullptr!");
    }
    if (space_ == 0)
    {
      shapePtr temp(new std::shared_ptr<Shape>[1]);
      space_ = 1;
      shapes_ = std::move(temp);
    }
    else if (space_ == size_)
    {
      shapePtr temp(new std::shared_ptr<Shape>[size_ * 2]);
      for (size_t i = 0; i < size_; i++)
      {
        temp[i] = shapes_[i];
      }
      space_ *= 2;
      shapes_ = std::move(temp);
    }
    shapes_[size_] = shape;
    size_++;
  }

  void CompositeShape::deleteShape(const size_t index)
  {
    if (size_ == 0|| index > (size_ - 1))
    {
      throw std::out_of_range("Index out of range! Invalid index: "
          + std::to_string(index));
    }
    for (size_t i = index + 1; i < size_; i++)
    {
      shapes_[i - 1] = shapes_[i];
    }
    shapes_[size_ - 1] = nullptr;
    size_--;
  }

  void CompositeShape::rotate(const double angle) noexcept
  {
    double angleRadian = angle * M_PI / (CIRCLE_ANGLE / 2);
    for (size_t i = 0; i < size_; i++)
    {
      double spotX = shapes_[i]->getCore().x - getCore().x;
      double spotY = shapes_[i]->getCore().y - getCore().y;
      const double diffX = (spotX * fabs(cos(angleRadian))) - (spotY * fabs(sin(angleRadian)));
      const double diffY = (spotX * fabs(sin(angleRadian))) + (spotY * fabs(cos(angleRadian)));
      shapes_[i]->move({getCore().x + diffX, getCore().y + diffY});
      shapes_[i]->rotate(angle);
    } 
  }

  Matrix CompositeShape::getMatrixLayer()
  {
    Matrix temp;
    for (size_t i = 0; i < size_; i++)
    {
      temp.addShape(shapes_[i]);
    }
    return temp;
  }

  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  size_t CompositeShape::getSpace() const noexcept
  {
    return space_;
  }
}
