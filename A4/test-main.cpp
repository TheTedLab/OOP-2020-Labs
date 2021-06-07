#define BOOST_TEST_MODULE test
#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY = 0.00001;
const double HALF_CIRCLE = 180.0;

BOOST_AUTO_TEST_CASE(test_invalid_add_shape_matrix)
{
  mukhin::Matrix matrix;
  std::shared_ptr<mukhin::Rectangle> rec = nullptr;
  BOOST_CHECK_THROW(matrix.addShape(rec), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_get_shape_matrix)
{
  mukhin::Matrix matrix;
  BOOST_CHECK_THROW(matrix.getShape(50,47), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_rotate)
{
  mukhin::Rectangle rec(50.0, 20.0, {0, 0});
  double recArea = rec.getArea();
  mukhin::point_t core = rec.getCore();
  double angle = 60.0;
  rec.rotate(angle);
  BOOST_CHECK_CLOSE(recArea, rec.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(core.x, rec.getCore().x, ACCURACY);
  BOOST_CHECK_CLOSE(core.y, rec.getCore().y, ACCURACY);
  BOOST_CHECK_CLOSE(50.0 * cos(angle * M_PI / HALF_CIRCLE) + 20.0 * sin(angle * M_PI / HALF_CIRCLE), rec.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(20.0 * cos(angle * M_PI / HALF_CIRCLE) + 50.0 * sin(angle * M_PI / HALF_CIRCLE) , rec.getFrameRect().height, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_rotate)
{
  mukhin::Circle cir(20.0, {5.0, 5.0});
  double cirArea = cir.getArea();
  mukhin::point_t core = cir.getCore();
  cir.rotate(60.8);
  BOOST_CHECK_CLOSE(cirArea, cir.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(core.x, cir.getCore().x, ACCURACY);
  BOOST_CHECK_CLOSE(core.y, cir.getCore().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_rotate)
{
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(10.0, {0.0, 0.0}));
  std::shared_ptr<mukhin::Shape> rec = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {0.0, 0.0}));
  mukhin::CompositeShape cShape(2);
  cShape.addShape(cir);
  cShape.addShape(rec);
  mukhin::point_t core = cShape.getCore();
  double commonArea = cShape.getArea();
  cShape.rotate(90.0);
  BOOST_CHECK_CLOSE(cShape.getCore().x, core.x, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getCore().y, core.y, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getArea(), commonArea, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().width, 20, ACCURACY);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().height, 20, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_matrix_add_one_shape)
{
  std::shared_ptr<mukhin::Shape> rec = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(50.0, 25.0, {0, 0}));
  mukhin::Matrix matrix;
  matrix.addShape(rec);
  BOOST_CHECK(matrix.getRows() == 1);
  BOOST_CHECK(matrix.getColumns() == 1);
}

BOOST_AUTO_TEST_CASE(test_adding_two_not_overlayed_shapes_matrix)
{
  std::shared_ptr<mukhin::Shape> rec = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(5.0, 2.0, {50.0, 50.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(10.0, {0.0, 0.0}));
  mukhin::Matrix matrix;
  matrix.addShape(rec);
  matrix.addShape(cir);
  BOOST_CHECK(matrix.getRows() == 1);
  BOOST_CHECK(matrix.getColumns() == 2);
}

BOOST_AUTO_TEST_CASE(test_adding_two_overlayed_shapes_matrix)
{
  std::shared_ptr<mukhin::Shape> rec = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(5.0, 2.0, {0.0, 0.0}));
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(10.0, {0.0, 0.0}));
  mukhin::Matrix matrix;
  matrix.addShape(rec);
  matrix.addShape(cir);
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 1);
}

BOOST_AUTO_TEST_CASE(test_get_shape_matrix)
{
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(5.0, {0.0, 0.0}));
  std::shared_ptr<mukhin::Shape> rec1 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(5.0, 10.0, {10.0, 0.0}));
  std::shared_ptr<mukhin::Shape> rec2 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(20.0, 5.0, {0.0, 0.0}));
  mukhin::Matrix matrix;
  matrix.addShape(cir);
  matrix.addShape(rec1);
  matrix.addShape(rec2);
  BOOST_CHECK(matrix.getShape(1,1) == nullptr);
  BOOST_CHECK(matrix.getShape(0,0) == cir);
  BOOST_CHECK(matrix.getShape(0,1) == rec1);
  BOOST_CHECK(matrix.getShape(1,0) == rec2);
}

BOOST_AUTO_TEST_CASE(test_matrix_layer_composite_shape)
{
  std::shared_ptr<mukhin::Shape> cir = std::make_shared<mukhin::Circle>(mukhin::Circle(4.0, {0.0, 4.0}));
  std::shared_ptr<mukhin::Shape> rec1 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(10.0, 20.0, {0.0, 0.0}));
  std::shared_ptr<mukhin::Shape> rec2 = std::make_shared<mukhin::Rectangle>(mukhin::Rectangle(6.0, 4.0, {-6.0, 0.0}));
  mukhin::CompositeShape cShape;
  cShape.addShape(cir);
  cShape.addShape(rec1);
  cShape.addShape(rec2);
  mukhin::Matrix matrixLayer = cShape.getMatrixLayer();
  BOOST_CHECK(matrixLayer.getColumns() == 1);
  BOOST_CHECK(matrixLayer.getRows() == 3);
}
