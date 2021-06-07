#include "commandHandler.hpp"
#include <sstream>
#include <cctype>
#include <algorithm>

std::string readName(std::istringstream & input)
{
  input.ignore();
  std::string name;
  std::getline(input, name);

  if (name.empty())
  {
    return name;
  }

  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  name.erase(std::remove(name.begin(), name.end(), '\\'), name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

bool isCorrectNumber(const std::string & number)
{
  for (auto & digit : number)
  {
    if (!std::isdigit((digit)))
    {
      return false;
    }
  }
  return !number.empty();
}

std::string readNumber(std::istringstream & input)
{
  std::string number;
  input >> number;

  if (!isCorrectNumber(number))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return number;
}

std::string readMark(std::istringstream & input)
{
  std::string markName;
  input >> markName;

  for (auto & symbol : markName)
  {
    if (!isalnum(symbol) && (symbol != '-'))
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  return markName;
}

commandFunction handler(const std::string & input)
{
  std::istringstream in(input);
  std::string command;
  in >> command;

  if (command == "add")
  {
    std::string number = readNumber(in);
    std::string name = readName(in);

    return [number, name](PhoneBookInterface & book)
    {
      book.addMark(PhoneBookInterface::Mark{ number, name });
    };
  }
  else if (command == "store")
  {
    std::string markName = readMark(in);
    std::string newMarkName = readMark(in);

    return [markName, newMarkName](PhoneBookInterface & book)
    {
      book.storeMark(markName, newMarkName);
    };
  }
  else if (command == "insert")
  {
    std::string position;
    in >> position;

    std::string markName = readMark(in);
    std::string number = readNumber(in);
    std::string name = readName(in);

    if (position == "before")
    {
      return [markName, number, name](PhoneBookInterface & book)
      {
        book.insertMarkBefore(PhoneBookInterface::Mark{ number, name }, markName);
      };
    }
    else if (position == "after")
    {
      return [markName, number, name](PhoneBookInterface & book)
      {
        book.insertMarkAfter(PhoneBookInterface::Mark{ number, name }, markName);
      };
    }
    else
    {
      return [](PhoneBookInterface &)
      {
        std::cout << "<INVALID COMMAND>\n";
      };
    }
  }
  else if (command == "delete")
  {
    std::string markName = readMark(in);

    return [markName](PhoneBookInterface & book)
    {
      book.deleteMark(markName);
    };
  }
  else if (command == "show")
  {
    std::string markName = readMark(in);

    return [markName](PhoneBookInterface & book)
    {
      book.showMark(markName);
    };
  }
  else if (command == "move")
  {
    std::string markName = readMark(in);
    std::string steps;
    in >> steps;

    if (steps == "first")
    {
      return [markName](PhoneBookInterface & book)
      {
        book.moveMark(markName, PhoneBookInterface::MovePosition::FIRST);
      };
    }
    else if (steps == "last")
    {
      return [markName](PhoneBookInterface & book)
      {
        book.moveMark(markName, PhoneBookInterface::MovePosition::LAST);
      };
    }
    else
    {
      if (!steps.empty())
      {
        int sign = 1;
        if (steps[0] == '-')
        {
          sign = -1;
          steps.erase(steps.begin());
        }
        else if (steps[0] == '+')
        {
          steps.erase(steps.begin());
        }

        if (isCorrectNumber(steps))
        {
          return [markName, steps, sign](PhoneBookInterface & book)
          {
            book.moveMark(markName, (std::stoi(steps) * sign));
          };
        }
        else
        {
          return [](PhoneBookInterface &)
          {
            std::cout << "<INVALID STEP>\n";
          };
        }
      }
      else
      {
        return [](PhoneBookInterface &)
        {
          std::cout << "<INVALID STEP>\n";
        };
      }
    }
  }
  else 
  {
    return [](PhoneBookInterface &)
    {
      std::cout << "<INVALID COMMAND>\n";
    };
  }
}
