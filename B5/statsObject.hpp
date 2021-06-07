#ifndef STATS_OBJECT_HPP
#define STATS_OBJECT_HPP

#include "shape.hpp"

class StatsObject
{
public:

  StatsObject();

  void operator()(Shape & shape);

  friend std::ostream& operator<<(std::ostream& os, const StatsObject & stats);

private:
  size_t verticesCount_;
  size_t triangleCount_;
  size_t squareCount_;
  size_t rectangleCount_;
};

#endif
