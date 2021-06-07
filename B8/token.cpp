#include "token.hpp"

Token::Token() : 
  data_(""),
  type_(TokenType::UNKNOWN)
{}

Token::Token(std::string data, const TokenType type) :
  data_(std::move(data)),
  type_(type)
{}
