#ifndef TASK_ONE_HPP
#define TASK_ONE_HPP

#include <iostream>
#include <stdexcept>
#include "priorityQueue.hpp"

template <typename T>
void add(priorityQueue<T> & queue, std::istream & sin, std::ostream & os)
{
  std::string priority;
  sin >> priority;
  if (priority.empty())
  {
    os << "<INVALID COMMAND>\n";
    return;
  }

  std::string data;
  sin >> data;

  if (!sin.eof())
  {
    std::string additional_data;
    std::getline(sin, additional_data);
    data += additional_data;
  }

  if (data.empty())
  {
    os << "<INVALID COMMAND>\n";
    return;
  }

  if (priority == "high")
  {
    queue.pushElement(data, priorityQueue<T>::elementPriority::HIGH);
  }
  else if (priority == "normal")
  {
    queue.pushElement(data, priorityQueue<T>::elementPriority::NORMAL);
  }
  else if (priority == "low")
  {
    queue.pushElement(data, priorityQueue<T>::elementPriority::LOW);
  }
  else
  {
    os << "<INVALID COMMAND>\n";
    return;
  }
}

template <typename T>
void get(priorityQueue<T> & queue, std::ostream & os)
{
  if (!queue.isEmpty())
  {
    os << queue.getElement() << '\n';
    queue.popElement();
  }
  else
  {
    os << "<EMPTY>\n";
  }
}

template <typename T>
void accelerate(priorityQueue<T> & queue)
{
  queue.accelerate();
}

template <typename T>
void processCommand(priorityQueue<T> & queue, std::string & command, std::ostream & os)
{
  if (command == "add")
  {
    add(queue, std::cin, os);
  }
  else if (command == "get")
  {
    get(queue, os);
  }
  else if (command == "accelerate")
  {
    accelerate(queue);
  }
  else if (command != "")
  {
    os << "<INVALID COMMAND>\n";
  }
}

void task_1()
{
  priorityQueue<std::string> queue;
  while (!std::cin.eof() && std::cin.good())
  {
    std::string command;
    std::cin >> command;
    processCommand(queue, command, std::cout);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task_1!\n");
  }
}

#endif
