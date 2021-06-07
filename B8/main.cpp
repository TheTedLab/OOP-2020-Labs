#include <iostream>
#include <string>
#include "task.hpp"

const int STANDARD_LENGTH = 40;
const int MIN_LENGTH = 25;

int main(int argc, char * argv[])
{
  try
  {
    int lineLength = STANDARD_LENGTH;
    if (argc == 1)
    {
      task(lineLength, std::cin, std::cout);
    }
    else if (argc == 3)
    {
      const std::string argument = std::string(argv[1]);
      if (argument != "--line-width")
      {
        throw std::invalid_argument("Invalid args format!\n");
      }
      lineLength = std::atoi(argv[2]);
      if (lineLength < MIN_LENGTH)
      {
        throw std::invalid_argument("Invalid line length!\n");
      }
      task(lineLength, std::cin, std::cout);
    }
    else
    {
      throw std::invalid_argument("Invalid number of args!\n");
    }
  }
  catch(const std::exception &err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error!\n";
    return 2;
  }
  return 0;
}
