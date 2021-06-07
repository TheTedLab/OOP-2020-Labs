#include "phoneBookInterface.hpp"

PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook>&& book)
{
  phoneBook_ = std::move(book);
  marks_["current"] = phoneBook_->begin();
}

void PhoneBookInterface::addMark(const Mark & mark)
{
  phoneBook_->pushBack(mark);
  if (phoneBook_->size() == 1)
  {
    marks_["current"] = phoneBook_->begin();
  }
}

void PhoneBookInterface::storeMark(const std::string & markName, const std::string & newMarkName)
{
  auto iter = marks_.find(markName);
  if (iter != marks_.end())
  {
    marks_[newMarkName] = iter->second;
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::insertMarkBefore(const Mark & mark, const std::string & markName)
{
  if (markName == "current" && phoneBook_->size() == 0)
  {
    addMark(mark);
  }
  else
  {
    auto iter = marks_.find(markName);
    if (iter != marks_.end())
    {
      phoneBook_->insertNote(iter->second, mark);
      if (marks_.size() == 1)
      {
        marks_["current"] = phoneBook_->begin();
      }
    }
    else
    {
      std::cout << "<INVALID BOOKMARK>\n";
    }
  }
}

void PhoneBookInterface::insertMarkAfter(const Mark & mark, const std::string & markName)
{
  if (markName == "current" && phoneBook_->size() == 0)
  {
    addMark(mark);
  }
  else
  {
    auto iter = marks_.find(markName);
    if (iter != marks_.end())
    {
      phoneBook_->insertNote(std::next(iter->second), mark);
      if (marks_.size() == 1)
      {
        marks_["current"] = phoneBook_->begin();
      }
    }
    else
    {
      std::cout << "<INVALID BOOKMARK>\n";
    }
  }
}

void PhoneBookInterface::deleteMark(const std::string & markName)
{
  auto iter = marks_.find(markName);
  if (iter == marks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  else
  {
    auto deleteIter = iter->second;
    for (auto i = marks_.begin(); i != marks_.end(); i++)
    {
      if (i->second == deleteIter)
      {
        if (std::next(i->second) == phoneBook_->end())
        {
          i->second = phoneBook_->begin();
        }
        else
        {
          i->second = std::next(deleteIter);
        }
      }
    }
    phoneBook_->eraseNote(deleteIter);
  }
}

void PhoneBookInterface::showMark(const std::string & markName)
{
  auto iter = marks_.find(markName);
  if (iter == marks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  if (phoneBook_->size() == 0)
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  phoneBook_->showNote(iter->second);
}

void PhoneBookInterface::moveMark(const std::string & markName, int steps)
{
  auto iter = marks_.find(markName);
  if (iter == marks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
  else
  {
    int count = 0;
    if (steps > 0)
    {
      while (count != steps && iter->second != std::prev(phoneBook_->end()))
      {
        iter->second = std::next(iter->second);
        ++count;
      }
    }
    else if (steps < 0)
    {
      while (count != steps && iter->second != phoneBook_->begin())
      {
        iter->second = std::prev(iter->second);
        --count;
      }
    }
  }
}

void PhoneBookInterface::moveMark(const std::string & markName, MovePosition pos)
{
  auto iter = marks_.find(markName);
  if (iter == marks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
  else
  {
    switch(pos)
    {
    case MovePosition::FIRST:
      iter->second = phoneBook_->begin();
      break;
    case MovePosition::LAST:
      iter->second = std::prev(phoneBook_->end());
      break;
    }
  }
}
