#pragma once

#include "../settings.hpp"
#include "vector_definition.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace phoenixofhp_stl {

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0){};

template <typename T> vector<T>::~vector() { delete[] data_; };

template <typename T> vector<T>::vector(size_t initial_capacity) : size_(0) {
  reallocate(initial_capacity);
};

template <typename T>
vector<T>::vector(const vector &copy)
    : data_(nullptr), size_(0), capacity_(0) {
  if (!copy.empty()) {
    reallocate(copy.size());
    std::copy(copy.data(), copy.data() + copy.size(), this->data());
    size_ = copy.size();
  }
};

template <typename T>
vector<T>::vector(vector &&move) noexcept
    : data_(move.data_), size_(move.size_), capacity_(move.capacity_) {
  move.data_ = nullptr;
  move.size_ = 0;
  move.capacity_ = 0;
};

template <typename T>
vector<T> &vector<T>::operator=(const vector &copy)
{
  if (this != &copy) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    if (!copy.empty()) {
      reallocate(copy.size());
      std::copy(copy.data(), copy.data() + copy.size(), this->data());
      size_ = copy.size();
    }
  }
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&move) noexcept
{
  if (this != &move) {
    delete[] data_;
    data_ = move.data_;
    size_ = move.size_;
    capacity_ = move.capacity_;
    move.data_ = nullptr;
    move.size_ = 0;
    move.capacity_ = 0;
  }
  return *this;
}

template <typename T> void vector<T>::reallocate(size_t new_capacity) {
  T *new_data = new T[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  if (data_ != nullptr) {
    delete[] data_;
  }
  data_ = new_data;
  capacity_ = new_capacity;
}

template <typename T> T &vector<T>::at(size_t i) {
  if (i >= size_) {
    throw std::out_of_range("vector<T::at");
  } else {
    return data_[i];
  }
}

template <typename T> const T &vector<T>::at(size_t i) const {
  if (i >= size_) {
    throw std::out_of_range("vector<T::at");
  } else {
    return data_[i];
  }
}

template <typename T> void vector<T>::push_back(const T &copy) {
  if (size_ == capacity_) {
    reallocate(capacity_ ? capacity_ * get_reallocate_factor() : 1);
  }
  data_[size_++] = copy;
}

template <typename T> void vector<T>::push_back(T &&move) {
  if (size_ == capacity_) {
    reallocate(capacity_ ? capacity_ * get_reallocate_factor() : 1);
  }
  data_[size_++] = std::move(move);
}

template <typename T>
unsigned vector<T>::get_reallocate_factor() const noexcept {
  return PHOENIXOFHP_STL_VECTOR_REALLOCATE_FACTOR_BASE;
}

} // namespace phoenixofhp_stl
