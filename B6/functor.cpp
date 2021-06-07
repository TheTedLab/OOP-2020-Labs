#include "functor.hpp"

Functor::Functor() :
  maxValue_(std::numeric_limits<int>::min()),
  minValue_(std::numeric_limits<int>::max()),
  positive_(0),
  negative_(0),
  amount_(0),
  first_(0),
  sumOfOdd_(0),
  sumOfEven_(0),
  isEqual(false)
{}

void Functor::operator()(int number)
{
  if (amount_ == 0)
  {
    first_ = number;
  }
  if (number > maxValue_)
  {
    maxValue_ = number;
  }
  if (number < minValue_)
  {
    minValue_ = number;
  }
  if (number > 0)
  {
    positive_++;
  }
  else if (number < 0)
  {
    negative_++;
  }
  if (number % 2 == 0)
  {
    sumOfEven_ += number;
  }
  else
  {
    sumOfOdd_ += number;
  }
  amount_++;
  isEqual = (first_ == number);
}

std::ostream & operator<<(std::ostream & os, const Functor & func)
{
  if (func.amount_ == 0)
  {
    os << "No Data\n";
    return os;
  }

  const auto average = static_cast<double>(func.sumOfEven_ + func.sumOfOdd_) / func.amount_;

  os << "Max: " << func.maxValue_ << '\n' 
      << "Min: " << func.minValue_ << '\n' 
      << "Mean: " << std::fixed << average << '\n' 
      << "Positive: " << func.positive_ << '\n'
      << "Negative: " << func.negative_ << '\n'
      << "Odd Sum: " << func.sumOfOdd_ << '\n'
      << "Even Sum: " << func.sumOfEven_ << '\n'
      << "First/Last Equal: " << (func.isEqual ? "yes" : "no") << '\n';
  return os;
}
