#include <iostream>
#include <stdexcept>
#include "task1.hpp"
#include "task2.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of input parameters!\n");
    }

    int task_number = std::atoi(argv[1]);
    if (task_number < 1 || task_number > 2)
    {
      throw std::invalid_argument("Invalid number of task!\n");
    }

    switch (task_number)
    {
    case 1:
      task1(std::cin, std::cout);
      break;
    case 2:
      task2(std::cin, std::cout);
      break;
    }
  }
  catch(const std::exception & err)
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
