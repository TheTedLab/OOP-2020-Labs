#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:
  enum class TokenType
  {
    WORD,
    NUMBER,
    DELIMITER,
    UNKNOWN
  };

  Token();
  Token(std::string data, const TokenType type);

  std::string data_;
  TokenType type_;
};

#endif
