cmake_minimum_required(VERSION 3.16)

project(phoenixofhp-stl-vector LANGUAGES CXX)

add_library(phoenixofhp_stl_vector INTERFACE)
add_library(phoenixofhp_stl::vector ALIAS phoenixofhp_stl_vector)

target_include_directories(phoenixofhp_stl_vector
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(phoenixofhp_stl_vector INTERFACE cxx_std_20)
