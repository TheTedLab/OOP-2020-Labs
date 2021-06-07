#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <list>
#include <stdexcept>

template <typename T>
class priorityQueue
{
public:
  enum class elementPriority
  {
    LOW = 0,
    NORMAL = 1,
    HIGH = 2
  }; //Define priorities explicitly, HIGH should remain the maximum and LOW the minimum
  void pushElement(const T& element, elementPriority priority);
  void popElement();
  T getElement() const;
  void accelerate();
  bool isEmpty() const noexcept;
private:
  static const int NUMBER_OF_PRIORITY = static_cast<int>(elementPriority::HIGH) - static_cast<int>(elementPriority::LOW) + 1;
  std::list<T> priorityList_[NUMBER_OF_PRIORITY];
};

template <typename T>
void priorityQueue<T>::pushElement(const T& element, elementPriority priority)
{
  priorityList_[static_cast<int>(priority)].push_back(element);
}

template <typename T>
void priorityQueue<T>::popElement()
{
  if (isEmpty())
  {
    throw std::logic_error("Priority Queue is underflow!\n");
  }

  for (int priority = NUMBER_OF_PRIORITY - 1; priority >= 0; priority--)
  {
    if (!priorityList_[priority].empty())
    {
      priorityList_[priority].pop_front();
      return;
    }
  }
}

template <typename T>
T priorityQueue<T>::getElement() const
{
  for (int priority = NUMBER_OF_PRIORITY - 1; priority >= 0; priority--)
  {
    if (!priorityList_[priority].empty())
    {
      return priorityList_[priority].front();
    }
  }
  throw std::logic_error("Priority Queue is underflow!\n");
}

template <typename T>
void priorityQueue<T>::accelerate()
{
  if (!priorityList_[0].empty())
  {
    priorityList_[NUMBER_OF_PRIORITY - 1].splice(priorityList_[NUMBER_OF_PRIORITY - 1].end(), priorityList_[0]);
  }
}

template <typename T>
bool priorityQueue<T>::isEmpty() const noexcept
{
  for (int priority = NUMBER_OF_PRIORITY - 1; priority >= 0; priority--)
  {
    if (!priorityList_[priority].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
