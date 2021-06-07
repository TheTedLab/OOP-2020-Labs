#include "figures.hpp"

void Circle::draw(std::ostream& os) const
{
  os << "CIRCLE " << this->core_ << '\n';
}

void Square::draw(std::ostream& os) const
{
  os << "SQUARE " << this->core_ << '\n';
}

void Triangle::draw(std::ostream& os) const
{
  os << "TRIANGLE " << this->core_ << '\n';
}
