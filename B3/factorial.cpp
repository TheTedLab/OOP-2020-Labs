#include "factorial.hpp"

Factorial::IteratorFact::IteratorFact():
  IteratorFact(1)
{}

Factorial::IteratorFact::IteratorFact(size_t pos):
  pos_(pos),
  value_(factor(pos))
{}

const size_t* Factorial::IteratorFact::operator->() const
{
  return &value_;
}

const size_t& Factorial::IteratorFact::operator*() const
{
  return value_;
}

Factorial::IteratorFact& Factorial::IteratorFact::operator++()
{
  if (pos_ < MAX_POS)
  {
    ++pos_;
    value_ *= pos_;
  }
  return *this;
}

Factorial::IteratorFact Factorial::IteratorFact::operator++(int)
{
  Factorial::IteratorFact temp = *this;
  this->operator++();
  return temp;
}

Factorial::IteratorFact& Factorial::IteratorFact::operator--()
{
  if (pos_ > MIN_POS)
  {
    value_ /= pos_;
    --pos_;
  }
  return *this;
}

Factorial::IteratorFact Factorial::IteratorFact::operator--(int)
{
  Factorial::IteratorFact temp = *this;
  this->operator--();
  return temp;
}

bool Factorial::IteratorFact::operator==(const Factorial::IteratorFact& rhs) const
{
  return (pos_ == rhs.pos_);
}

bool Factorial::IteratorFact::operator!=(const Factorial::IteratorFact& rhs) const
{
  return (pos_ != rhs.pos_);
}

inline size_t Factorial::IteratorFact::factor(size_t number)
{
  size_t result = 1;
  for (size_t i = 1; i <= number; ++i)
  {
    result *= i;
  }
  return result;
}

Factorial::IteratorFact Factorial::begin()
{
  return IteratorFact(IteratorFact::MIN_POS);
}

Factorial::IteratorFact Factorial::end()
{
  return IteratorFact(IteratorFact::MAX_POS);
}
