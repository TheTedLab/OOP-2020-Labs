#ifndef INPUT_ITERATOR_HPP
#define INPUT_ITERATOR_HPP

#include <iostream>
#include <iterator>
#include "token.hpp"

class InputIterator : public std::iterator<std::input_iterator_tag, Token>
{
public:
  explicit InputIterator(std::istream& sin);
  InputIterator();
  Token& operator*();
  Token* operator->();
  InputIterator& operator++();
  InputIterator operator++(int);
  bool operator==(const InputIterator& iter) const;
  bool operator!=(const InputIterator& iter) const;
private:
  std::istream* sin_;
  Token token_;
  bool condition_;
  void readText();
  void readWord();
  void readNumber();
  void readDelimiter();
};

#endif
