#ifndef TASK_TWO_HPP
#define TASK_TWO_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <vector>
#include "show.hpp"

void task_2(const char * file_name)
{
  std::ifstream fin(file_name);

  if (!fin.is_open())
  {
    throw std::invalid_argument("File can't be opened!\n");
  }

  size_t size = 16;
  size_t index = 0;

  using ArrayPtr = std::unique_ptr<char[], decltype(&std::free)>;
  ArrayPtr arr(static_cast<char*>(malloc(size)), std::free);

  if (arr == nullptr)
  {
    throw std::bad_alloc();
  }

  while (fin >> arr[index])
  {
    index++;
    if (size == index)
    {
      size *= 2;
      ArrayPtr temp(static_cast<char*>(realloc(arr.get(), size)), std::free);
      if (temp == nullptr)
      {
        throw std::bad_alloc();
      }
      arr.release();
      arr = std::move(temp);
    }
  }

  if (!fin.eof() && fin.fail())
  {
    throw std::runtime_error("Error while reading file!\n");
  }

  fin.close();

  if (fin.is_open())
  {
    throw std::runtime_error("Error while closing file!\n");
  }

  std::vector<char> output_vector(arr.get(), arr.get() + index);
  if (!output_vector.empty())
  {
    show(output_vector, "");
  }
}

#endif
