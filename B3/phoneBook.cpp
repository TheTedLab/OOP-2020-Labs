#include "phoneBook.hpp"

void PhoneBook::showNote(Iterator iter) const
{
  std::cout << iter->number_ << ' ' << iter->name_ << '\n';
}

PhoneBook::Iterator PhoneBook::insertNote(Iterator iter, const Note & note)
{
  return container_.insert(iter, note);
}

void PhoneBook::pushBack(const Note & note)
{
  container_.push_back(note);
}

PhoneBook::Iterator PhoneBook::eraseNote(Iterator iter)
{
  return container_.erase(iter);
}

PhoneBook::Iterator PhoneBook::begin() noexcept
{
  return container_.begin();
}

PhoneBook::Iterator PhoneBook::end() noexcept
{
  return container_.end();
}

int PhoneBook::size() const noexcept
{
  return container_.size();
}
