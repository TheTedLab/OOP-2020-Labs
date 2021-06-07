#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& sin, DataStruct& data);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);

#endif
