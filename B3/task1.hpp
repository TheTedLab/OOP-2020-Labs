#ifndef TASK_ONE_HPP
#define TASK_ONE_HPP

#include <iostream>
#include "phoneBookInterface.hpp"
#include "commandHandler.hpp"

void task_1()
{
  PhoneBook book;
  PhoneBookInterface phoneBook(std::make_unique<PhoneBook>(book));
  std::string input;
  while (std::getline(std::cin, input))
  {
    try
    {
      commandFunction comFunc = handler(input);
      comFunc(phoneBook);
    }
    catch (const std::invalid_argument & err)
    {
      std::cout << err.what();
      continue;
    }
    catch (const std::exception & err)
    {
      std::cerr << err.what() << '\n';
    }
  }
}

#endif
