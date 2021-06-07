#include <iostream>
#include "task.hpp"

int main()
{
  try
  {
    task(std::cin, std::cout);
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
