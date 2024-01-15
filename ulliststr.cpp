#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::push_back(const std::string& val)
{
  if(size_ == 0){
    Item *temp = new Item();
    temp->val[0] = val;
    temp->first = 0;
    temp->last = 1;
    head_ = temp;
    tail_ = temp;
    size_++;
  }
  else if(tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }
  else{
    Item *temp = new Item();
    temp->val[0] = val;
    temp->first = 0;
    temp->last = 1;
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
    size_++;
  }
}

void ULListStr::pop_back()
{
  if(size_ == 0){
    return;
  }
  else{
    tail_->last--;
    size_--;
    if(tail_->first == tail_->last){
      Item *temp = tail_->prev;
      delete tail_;
      tail_ = temp;
      if(tail_ == NULL){
        head_ = NULL;
      }
      else{
        tail_->next = NULL;
      }
    }
  }
}

void ULListStr::push_front(const std::string& val)
{
  if(size_ == 0){
    Item *temp = new Item();
    temp->val[0] = val;
    temp->first = 0;
    temp->last = 1;
    head_ = temp;
    tail_ = temp;
    size_++;
  }
  else if(head_->first > 0){
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
  }
  else{
    Item *temp = new Item();
    temp->val[0] = val;
    temp->first = 0;
    temp->last = 1;
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    size_++;
  }
}

void ULListStr::pop_front()
{
  if(size_ == 0){
    return;
  }
  else{
    head_->first++;
    size_--;
    if(head_->first == head_->last){
      Item *temp = head_->next;
      delete head_;
      head_ = temp;
      if(head_ == NULL){
        tail_ = NULL;
      }
      else{
        head_->prev = NULL;
      }
    }
  }
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc > size_){
    return NULL;
  }
  Item *temp = head_;
  while(loc >= temp->last-temp->first){
    loc -= temp->last-temp->first;
    temp = temp->next;
  }
  return &temp->val[temp->first+loc];
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
