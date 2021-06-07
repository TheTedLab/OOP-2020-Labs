#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <iostream>
#include <cstring>
#include "token.hpp"

class Functor
{
public:
  Functor(std::ostream & os, const unsigned int lineLength);
  ~Functor();
  void operator()(const Token & newToken);
private:
  const unsigned int lineLength_;
  std::string outputLine_;
  std::ostream& os_;
};

#endif
