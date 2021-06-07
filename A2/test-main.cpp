#define BOOST_TEST_MODULE test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(mukhin::Rectangle rectangle(5.5, -1.4, {9.7, 6.5}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(mukhin::Rectangle rectangle(-5.5, 1.4, {9.7, 6.5}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_factor_rectangle)
{
  mukhin::Rectangle rectangle(5.5, 1.4, {9.7, 6.5});
  BOOST_CHECK_THROW(rectangle.scale(-1.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_stability_rectangle_move)
{
  mukhin::Rectangle rectangle(5.5, 1.4, {9.7, 6.5});
  mukhin::rectangle_t rectFrame = rectangle.getFrameRect();
  double rectArea = rectangle.getArea();
  rectangle.move(0.3, 3.5);
  BOOST_CHECK_CLOSE(rectFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectArea, rectangle.getArea(), ACCURACY);
  mukhin::point_t rectMove {6.5, 9.7};
  rectangle.move(rectMove);
  BOOST_CHECK_CLOSE(rectFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectArea, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_rectangle_move)
{
  mukhin::point_t rectPos1 {9.7, 6.5};
  mukhin::Rectangle rectangle(5.5, 1.4, rectPos1);
  rectangle.move(0.3, 3.5);
  BOOST_CHECK_CLOSE(rectangle.getCore().x - 0.3, rectPos1.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getCore().y - 3.5, rectPos1.y, ACCURACY);
  mukhin::point_t rectPos2 {6.5, 9.7};
  rectangle.move(rectPos2);
  BOOST_CHECK_CLOSE(rectangle.getCore().x, rectPos2.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getCore().y, rectPos2.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scaling)
{
  mukhin::Rectangle rectangle (25.0, 25.0, {5.0, 5.0});
  double rectArea = rectangle.getArea();
  double factor = 1.5;
  rectangle.scale(factor);
  BOOST_CHECK_CLOSE(rectArea * factor * factor, rectangle.getArea(), ACCURACY);
  rectArea = rectangle.getArea();
  factor = 0.5;
  rectangle.scale(factor);
  BOOST_CHECK_CLOSE(rectArea * factor * factor, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(mukhin::Circle circle(-4.6, {5.4, 10.3}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_factor_circle)
{
  mukhin::Circle circle(4.6, {5.4, 10.3});
  BOOST_CHECK_THROW(circle.scale(-2.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_stability_circle_move)
{
  mukhin::Circle circle(10.0, {12.5, 25.0});
  mukhin::rectangle_t cirFrame = circle.getFrameRect();
  double cirArea = circle.getArea();
  circle.move(12.5, 5.0);
  BOOST_CHECK_CLOSE(cirFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(cirFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(cirArea, circle.getArea(), ACCURACY);
  mukhin::point_t cirMove {50.0, 5.0};
  circle.move(cirMove);
  BOOST_CHECK_CLOSE(cirFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(cirFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(cirArea, circle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_circle_move)
{
  mukhin::point_t cirPos1 {5.4, 10.3};
  mukhin::Circle circle(10.0, cirPos1);
  circle.move(4.6, 0.7);
  BOOST_CHECK_CLOSE(circle.getCore().x - 4.6, cirPos1.x, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getCore().y - 0.7, cirPos1.y, ACCURACY);
  mukhin::point_t cirPos2 {12.5, 12.5};
  circle.move(cirPos2);
  BOOST_CHECK_CLOSE(circle.getCore().x, cirPos2.x, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getCore().y, cirPos2.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_scaling)
{
  mukhin::Circle circle(10.0, {12.5, 25.0});
  double cirArea = circle.getArea();
  double factor = 1.5;
  circle.scale(factor);
  BOOST_CHECK_CLOSE(cirArea * factor * factor, circle.getArea(), ACCURACY);
  cirArea = circle.getArea();
  factor = 0.5;
  circle.scale(factor);
  BOOST_CHECK_CLOSE(cirArea * factor * factor, circle.getArea(), ACCURACY);
}
