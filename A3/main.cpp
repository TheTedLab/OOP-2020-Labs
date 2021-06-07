#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    mukhin::point_t recPoint = { 12.5, 25.0 };
    mukhin::point_t cirPoint = { 25.0, 12.5 };
    mukhin::Rectangle rec(40.0, 80.0, recPoint);
    mukhin::Circle cir(5.0, cirPoint);
    std::cout << "Rectangle info:\nWidth and Height: "
        << rec.getWidth() << " " << rec.getHeight()
        << "\nArea: " << rec.getArea()
        << "\nFrame:\n  Width: " << rec.getFrameRect().width
        << " Height: " << rec.getFrameRect().height
        << "\nCenter:\n  X: " << rec.getCore().x
        << " Y: " << rec.getCore().y
        << "\nMoving by coordinates...\n";
    rec.move(12.5, 25.0);
    std::cout << "Center:\n  X: " << rec.getCore().x
        << " Y: " << rec.getCore().y
        << "\nMoving by center...\n";
    mukhin::point_t recMovePoint = { 50.0, 50.0 };
    rec.move(recMovePoint);
    std::cout << "Center:\n  X: " << rec.getCore().x
        << " Y: " << rec.getCore().y
        << "\n\nCircle info:\nRadius: " << cir.getRadius()
        << "\nArea: " << cir.getArea()
        << "\nFrame:\n  Width: " << cir.getFrameRect().width
        << " Height: " << cir.getFrameRect().height
        << "\nCenter:\n  X: " << cir.getCore().x
        << " Y: " << cir.getCore().y
        << "\nMoving by coordinates...\n";
    cir.move(50.0, 112.5);
    std::cout << "Center:\n  X: " << cir.getCore().x
        << " Y: " << cir.getCore().y
        << "\nMoving by center...\n";
    mukhin::point_t cirMovePoint = { 100.0, 100.0 };
    cir.move(cirMovePoint);
    std::cout << "Center:\n  X: " << cir.getCore().x
        << " Y: " << cir.getCore().y
        << "\n\nTesting Polymorphism:\n";
    mukhin::Shape* shape = &cir;
    std::cout << "Shape pointer indicates to a circle:\n"
        << "  Shape Area: " << shape->getArea() << "\n";
    shape = &rec;
    std::cout << "Shape pointer indicates to a rectangle:\n"
        << "  Shape Area: " << shape->getArea()
        << "\n\nTesting Scale:\nRectangle width and height before scaling: "
        << rec.getWidth() << " " << rec.getHeight()
        << "\nScaling...\n";
    shape->scale(1.5);
    std::cout << "Rectangle width and height after scaling: "
        << rec.getWidth() << " " << rec.getHeight()
        << "\nCircle radius before scaling: "
        << cir.getRadius()
        << "\nScaling...\n";
    shape = &cir;
    shape->scale(1.5);
    std::cout << "Circle radius after scaling: "
        << cir.getRadius()
        << "\n\nTesting CompositeShape:\n";
    mukhin::CompositeShape cShape(2);
    mukhin::CompositeShape copyShape;
    std::cout << "Size of CompositeShape:  " << cShape.getSize() 
        << "\nSpace of CompositeShape: " << cShape.getSpace()
        << "\n\nAdding first shape...\n";
    std::shared_ptr<mukhin::Shape> shapePointer = std::make_shared<mukhin::Circle>(cir);
    cShape.addShape(shapePointer);
    std::cout << "Size of CompositeShape:  " << cShape.getSize()
        << "\nSpace of CompositeShape: " << cShape.getSpace()
        << "\n\nAdding second shape...\n";
    shapePointer = std::make_shared<mukhin::Rectangle>(rec);
    cShape.addShape(shapePointer);
    std::cout << "Size of CompositeShape:  " << cShape.getSize()
        << "\nSpace of CompositeShape: " << cShape.getSpace()
        << "\n\nAdding third shape...\n";
    shapePointer = std::make_shared<mukhin::Circle>(mukhin::Circle(10.0, {10.0, 20.0}));
    cShape.addShape(shapePointer);
    std::cout << "Size of CompositeShape:  " << cShape.getSize()
        << "\nSpace of CompositeShape: " << cShape.getSpace()
        << "\n\nArea of first shape in CompositeShape: " << cShape[0]->getArea()
        << "\nArea of second shape in CompositeShape: " << cShape[1]->getArea()
        << "\nArea of third shape in CompositeShape: " << cShape[2]->getArea()
        << "\nTotal Area of CompositeShape: " << cShape.getArea()
        << "\nCommon height and width of CompositeShape frame: " 
        << "\n Height: " << cShape.getFrameRect().height << " Width: "
        << cShape.getFrameRect().width
        << "\n\nCopying cShape into copyShape...\n";
    copyShape = cShape;
    std::cout << "Copy testing on copyShape:\n"
        << "Size of copyShape:  " << copyShape.getSize()
        << "\nSpace if copyShape: " << copyShape.getSpace()
        << "\nTotal Area of copyShape: " << copyShape.getArea()
        << "\nCommon height and width of copyShape frame: "
        << "\nHeight: " << copyShape.getFrameRect().height << " Width: "
        << copyShape.getFrameRect().width
        << "\nArea of first shape in copyShape: " << copyShape[0]->getArea()
        << "\nArea of second shape in copyShape: " << copyShape[1]->getArea()
        << "\nArea of third shape in copyShape: " << copyShape[2]->getArea()
        << "\n";
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch(const std::out_of_range& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error!\n";
    return 2;
  }
  return 0;
}
