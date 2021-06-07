#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <iostream>
#include <string>
#include <list>

class PhoneBook
{
public:
  struct Note
  {
    std::string number_;
    std::string name_;
  };

  using Container = std::list<Note>;
  using Iterator = Container::iterator;

  void showNote(Iterator iter) const;
  Iterator insertNote(Iterator iter, const Note & note);
  void pushBack(const Note & note);
  Iterator eraseNote(Iterator iter);
  Iterator begin() noexcept;
  Iterator end() noexcept;
  int size() const noexcept;

private:
  Container container_;
};

#endif
