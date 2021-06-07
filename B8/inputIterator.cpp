#include "inputIterator.hpp"
#include "constants.hpp"

InputIterator::InputIterator(std::istream& sin) :
  sin_(&sin),
  token_("", Token::TokenType::UNKNOWN),
  condition_(true)
{
  readText();
}

InputIterator::InputIterator() :
  sin_(nullptr),
  token_("", Token::TokenType::UNKNOWN),
  condition_(false)
{}

Token& InputIterator::operator*()
{
  return token_;
}

Token* InputIterator::operator->()
{
  return &token_;
}

InputIterator& InputIterator::operator++()
{
  readText();
  return *this;
}

InputIterator InputIterator::operator++(int)
{
  InputIterator *iter = this;
  readText();
  return *iter;
}

bool InputIterator::operator==(const InputIterator& iter) const
{
  return (condition_ == iter.condition_) && (!condition_ || sin_ == iter.sin_);
}

bool InputIterator::operator!=(const InputIterator& iter) const
{
  return !(operator==(iter));
}

void InputIterator::readText()
{
  (*sin_) >> std::ws;
  char current = sin_->get();
  char next = sin_->peek();

  if ((*sin_).fail())
  {
    condition_ = false;
    return;
  }

  if (isalpha(current))
  {
    sin_->unget();
    readWord();
  }
  else if (isdigit(current) || ((current == MINUS || current == PLUS) && isdigit(next)))
  {
    sin_->unget();
    readNumber();
  }
  else if (ispunct(current))
  {
    if (token_.data_.empty())
    {
      throw std::invalid_argument("Text must not start with punctuation!\n");
    }
    if (token_.type_ != Token::TokenType::DELIMITER)
    {
      sin_->unget();
      readDelimiter();
    }
    else if (token_.data_ == "," && current == HYPHEN)
    {
      sin_->unget();
      readDelimiter();
    }
    else
    {
      throw std::invalid_argument("Punctuation can't be after another punctuation!\n");
    }
  }
  else
  {
    throw std::invalid_argument("Unexpected symbol!\n");
  }
}

void InputIterator::readWord()
{
  Token token("", Token::TokenType::WORD);

  while (isalpha(sin_->peek()) || sin_->peek() == HYPHEN)
  {
    char letter = sin_->get();
    if (token.data_.size() >= MAX_WORD_LENGTH)
    {
      throw std::invalid_argument("Invalid length of word! Length must be less than 20!");
    }
    if (letter == HYPHEN && sin_->peek() == HYPHEN)
    {
      throw std::invalid_argument("Invalid word input! Double symbol '-' while reading!\n");
    }
    token.data_.push_back(letter);
  }

  token_ = token;
}

void InputIterator::readNumber()
{
  Token token("", Token::TokenType::NUMBER);

  const char decimalPoint = std::use_facet<std::numpunct<char> >(std::locale()).decimal_point();
  bool isDecimal = false;

  char symbol = sin_->get();
  token.data_.push_back(symbol);

  while (isdigit(sin_->peek()) || sin_->peek() == decimalPoint)
  {
    symbol = sin_->get();
    if (symbol == decimalPoint)
    {
      if (isDecimal)
      {
        throw std::invalid_argument("Invalid number format!");
      }
      isDecimal = true;
    }
    token.data_.push_back(symbol);
    if (token.data_.size() > MAX_WORD_LENGTH)
    {
      throw std::invalid_argument("Invalid length of number! Length must be less than 20!");
    }
  }

  token_ = token;
}

void InputIterator::readDelimiter()
{
  Token token("", Token::TokenType::DELIMITER);

  if (sin_->peek() != HYPHEN)
  {
    if (token_.type_ == Token::TokenType::DELIMITER)
    {
      throw std::invalid_argument("Two punctuation marks cannot follow each other!\n");
    }
    token.data_.push_back(sin_->get());
  }
  else
  {
    if (token_.type_ == Token::TokenType::DELIMITER && token_.data_ != ",")
    {
      throw std::invalid_argument("Two punctuation marks cannot follow each other!\n");
    }
    for (int i = 0; i < DASH_LENGTH; i++)
    {
      if (sin_->get() != HYPHEN)
      {
        throw std::invalid_argument("Unexpected symbol during reading dash!\n");
      }
    }
    token.data_ += DASH;
  }

  token_ = token;
}
