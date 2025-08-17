#pragma once
#include "vector_fwd.hpp"

namespace phoenixofhp_stl {

template <typename T> T *begin(vector<T> &v) noexcept { return v.data(); }

template <typename T> T *end(vector<T> &v) noexcept {
  return v.data() + v.size();
}

template <typename T> const T *begin(const vector<T> &v) noexcept {
  return v.data();
}

template <typename T> const T *end(const vector<T> &v) noexcept {
  return v.data() + v.size();
}

} // namespace phoenixofhp_stl