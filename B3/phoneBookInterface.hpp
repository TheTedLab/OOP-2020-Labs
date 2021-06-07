#ifndef PHONE_BOOK_INTERFACE_HPP
#define PHONE_BOOK_INTERFACE_HPP

#include <map>
#include <memory>
#include "phoneBook.hpp"

class PhoneBookInterface
{
public:

  enum class MovePosition 
  {
    FIRST,
    LAST
  };

  using Mark = PhoneBook::Note;

  PhoneBookInterface(std::unique_ptr<PhoneBook>&& book);
  void addMark(const Mark & mark);
  void storeMark(const std::string & markName, const std::string & newMarkName);
  void insertMarkBefore(const Mark & mark, const std::string & markName);
  void insertMarkAfter(const Mark & mark, const std::string & markName);
  void deleteMark(const std::string & markName);
  void showMark(const std::string & markName);
  void moveMark(const std::string & markName, int steps);
  void moveMark(const std::string & markName, MovePosition pos);

private:
  std::unique_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::Iterator> marks_;
};

#endif
