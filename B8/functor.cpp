#include "functor.hpp"
#include "constants.hpp"

Functor::Functor(std::ostream& os, const unsigned int lineLength) :
  lineLength_(lineLength),
  outputLine_(),
  os_(os)
{}

Functor::~Functor()
{
  if (!outputLine_.empty())
  {
    os_ << outputLine_ << NEW_LINE;
  }
}

void Functor::operator()(const Token& newToken)
{
  using TokenType = Token::TokenType;
  if (newToken.type_ == TokenType::WORD || newToken.type_ == TokenType::NUMBER)
  {
    if ((outputLine_.size() + newToken.data_.size() + 1) > lineLength_)
    {
      os_ << outputLine_ << NEW_LINE;
      outputLine_.clear();
    }
    else if (!outputLine_.empty())
    {
      outputLine_ += SPACE;
    }
    outputLine_ += newToken.data_;
  }
  else
  {
    if ((newToken.data_ == DASH && (outputLine_.size() + strlen(DASH) + 1) > lineLength_) ||
        ((outputLine_.size() + 1) > lineLength_))
    {
      const unsigned int lastSpace = outputLine_.find_last_of(SPACE);
      const unsigned int newLineLength = outputLine_.size() - lastSpace;
      std::string newOutputLine = outputLine_.substr(lastSpace, newLineLength);
      outputLine_.erase(lastSpace, newLineLength);
      newOutputLine.erase(0, 1);
      os_ << outputLine_ << NEW_LINE;
      outputLine_ = newOutputLine;
    }
    if (newToken.data_ == DASH)
    {
      outputLine_ += SPACE;
    }
    outputLine_ += newToken.data_;
  }
}
