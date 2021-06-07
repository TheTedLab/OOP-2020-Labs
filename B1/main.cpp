#include <iostream>
#include <cstdlib>
#include <exception>
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if (argc < 2 || argc > 4)
    {
      throw std::invalid_argument("Invalid count of input parameters!\n");
    }
    int task_number = std::atoi(argv[1]);
    if (task_number < 1 || task_number > 4)
    {
      throw std::invalid_argument("Invalid number of task!\n");
    }
    switch(task_number)
    {
    case 1:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid number of parameters!\n");
      }
      task_1(argv[2]);
      break;
    case 2:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid number of parameters!\n");
      }
      task_2(argv[2]);
      break;
    case 3:
      if (argc != 2)
      {
        throw std::invalid_argument("Invalid number of parameters!\n");
      }
      task_3();
      break;
    case 4:
      if (argc != 4)
      {
        throw std::invalid_argument("Invalid number of parameters!\n");
      }
      int size = std::atoi(argv[3]);
      task_4(argv[2], size);
      break;
    }
  }
  catch(const std::exception& err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unkown error!\n";
    return 2;
  }
  return 0;
}
