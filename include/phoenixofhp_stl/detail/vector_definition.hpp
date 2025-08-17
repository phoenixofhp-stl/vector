#pragma once

#include <cstddef>

namespace phoenixofhp_stl {
template <typename T> class vector {
public:
  vector();
  ~vector();

  vector(size_t initial_capacity);

  vector(const vector &copy_);
  vector &operator=(const vector &copy_);

  vector(vector &&move_) noexcept;
  vector &operator=(vector &&move_) noexcept;

  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return capacity_; }
  bool empty() const noexcept { return size_ == 0; }

  T &operator[](size_t i) { return data_[i]; };
  const T &operator[](size_t i) const { return data_[i]; };
  ;

  T &at(size_t i);
  const T &at(size_t i) const;

  void push_back(const T &copy);
  void push_back(T &&move);

private:
  unsigned get_reallocate_factor() const noexcept;
  void reallocate(size_t new_capacity);

  T *data_;
  size_t size_;
  size_t capacity_;
};
} // namespace phoenixofhp_stl
