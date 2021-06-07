#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try
  {
    point_t recPoint = { 12.5, 25.0 };
    point_t cirPoint = { 25.0, 12.5 };
    Rectangle rec(40.0, 80.0, recPoint);
    Circle cir(5.0, cirPoint);
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
    point_t recMovePoint = { 50.0, 50.0 };
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
    point_t cirMovePoint = { 100.0, 100.0 };
    cir.move(cirMovePoint);
    std::cout << "Center:\n  X: " << cir.getCore().x
        << " Y: " << cir.getCore().y
        << "\n\nTesting Polymorphism:\n";
    Shape* shape = &cir;
    std::cout << "Shape pointer indicates to a circle:\n" 
        << "  Shape Area: " << shape->getArea() << "\n";
    shape = &rec;
    std::cout << "Shape pointer indicates to a rectangle:\n" 
        << "  Shape Area: " << shape->getArea() << "\n";
  }
  catch(const std::invalid_argument& error)
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
