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
vector<T>::vector(const vector &copy_)
    : data_(nullptr), size_(0), capacity_(0) {
  if (!copy_.empty()) {
    reallocate(copy_.size());
    std::copy(copy_.data(), copy_.data() + copy_.size(), this->data());
    size_ = copy_.size();
  }
};

template <typename T>
vector<T>::vector(vector &&move_) noexcept
    : data_(move_.data_), size_(move_.size_), capacity_(move_.capacity_) {
  move_.data_ = nullptr;
  move_.size_ = 0;
  move_.cap_ = 0;
};

// vector &operator=(const vector &copy_);
// vector &operator=(vector &&move_);

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
