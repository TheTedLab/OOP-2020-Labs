#define BOOST_TEST_MODULE test
#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_scale_factor_composite_shape)
{
  mukhin::CompositeShape cShape;
  BOOST_CHECK_THROW(cShape.scale(-3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_operator_index_composite_shape)
{
  mukhin::CompositeShape cShape(3);
  BOOST_CHECK_THROW(cShape[-1], std::out_of_range);
  BOOST_CHECK_THROW(cShape[4], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_add_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> shapePointer = nullptr;
  BOOST_CHECK_THROW(cShape.addShape(shapePointer), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_delete_composite_shape)
{
  mukhin::CompositeShape cShape(1);
  BOOST_CHECK_THROW(cShape.deleteShape(-1), std::out_of_range);
  BOOST_CHECK_THROW(cShape.deleteShape(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_add_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {5.0, 10.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(20.0, {0.0, 0.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  BOOST_CHECK(cShape[0] == rect);
  BOOST_CHECK(cShape[1] == cir);
}

BOOST_AUTO_TEST_CASE(test_delete_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {5.0, 10.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(20.0, {0.0, 0.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  BOOST_CHECK(cShape.getSize() == 2);
  cShape.deleteShape(1);
  BOOST_CHECK(cShape.getSize() == 1);
  cShape.deleteShape(0);
  BOOST_CHECK(cShape.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_get_size_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {5.0, 10.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(20.0, {0.0, 0.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  BOOST_CHECK(cShape.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(test_get_space_composite_shape)
{
  mukhin::CompositeShape cShape(5);
  BOOST_CHECK(cShape.getSpace() == 5);
}

BOOST_AUTO_TEST_CASE(test_get_frame_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 10.0, {0.0, 0.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(5.0, {10.0, 10.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  const double cHeight = 20;
  const double cWidth = 20;
  BOOST_CHECK_CLOSE(cShape.getFrameRect().height, cHeight, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().width, cWidth, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_get_area_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(25.0, {0.0, 0.0}));
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {30.0, 0.0}));
  cShape.addShape(cir);
  cShape.addShape(rect);
  const double totalArea = cir->getArea() + rect->getArea();
  BOOST_CHECK_CLOSE(cShape.getArea(), totalArea, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_get_core_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect1 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {5.0, 10.0}));
  std::shared_ptr<mukhin::Shape> rect2 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {15.0, 10.0}));
  cShape.addShape(rect1);
  cShape.addShape(rect2);
  const double top = 20.0;
  const double bottom = 0.0;
  const double right = 20.0;
  const double left = 0.0;
  BOOST_CHECK_CLOSE(cShape.getCore().x, (right + left) / 2, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getCore().y, (top + bottom) / 2, ACCURACY); 
}

BOOST_AUTO_TEST_CASE(test_move_coordinates_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {5.0, 10.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(5.0, {15.0, 10.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  const double originalX = cShape.getFrameRect().pos.x;
  const double originalY = cShape.getFrameRect().pos.y;
  const double movingX = 10.0;
  const double movingY = 50.0;
  cShape.move(movingX, movingY);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.x, (originalX + movingX), ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.y, (originalY + movingY), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_move_point_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect1 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {5.0, 10.0}));
  std::shared_ptr<mukhin::Shape> rect2 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {15.0, 10.0}));
  cShape.addShape(rect1);
  cShape.addShape(rect2);
  const double movingX = 50.0;
  const double movingY = 10.0;
  mukhin::point_t movePoint{movingX, movingY};
  cShape.move(movePoint);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.x, movingX, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.y, movingY, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_scale_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {30.0, 0.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(25.0, {0.0, 0.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  const double rectArea = rect->getArea();
  const double cirArea = cir->getArea();
  const double totalArea = cShape.getArea();
  const double factor = 5.0;
  cShape.scale(factor);
  BOOST_CHECK_CLOSE(rectArea * factor * factor, rect->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(cirArea * factor * factor, cir->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(totalArea * factor * factor, cShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_copy_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {30.0, 0.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(25.0, {0.0, 0.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  mukhin::CompositeShape copyShape = cShape;
  BOOST_CHECK_CLOSE(cShape.getArea(), copyShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_displacement_composite_shape)
{
  mukhin::CompositeShape cShape;
  std::shared_ptr<mukhin::Shape> rect = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {30.0, 0.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(25.0, {0.0, 0.0}));
  cShape.addShape(rect);
  cShape.addShape(cir);
  const double totalArea = cShape.getArea();
  mukhin::CompositeShape displaceShape(std::move(cShape));
  BOOST_CHECK_CLOSE(displaceShape.getArea(), totalArea, ACCURACY);
  BOOST_CHECK_THROW(cShape[0], std::out_of_range);
  BOOST_CHECK_THROW(cShape[1], std::out_of_range);
}
