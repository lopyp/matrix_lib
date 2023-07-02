cmake_minimum_required(VERSION 3.14)
project(matr_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic -g")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  matr_test
  s21_matrix_oop.h
  s21_mainfunction.cc
  s21_overload.cc
  s21_private.cc
  s21_public.cc
  tests/matr_test.cc 
)

target_link_libraries(
  matr_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matr_test)

