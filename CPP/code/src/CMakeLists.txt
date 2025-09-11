cmake_minimum_required(VERSION 3.10)
project(Bootcamp
  DESCRIPTION "C++ Bootcamp"
  LANGUAGES C CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION MATCHES "^14.")
    message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
  else()
    message(WARNING "!! We recommend that you use clang-14 for this bootcamp. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, a different version.")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
else()
  message(WARNING "!! We recommend that you use clang-14 for this bootcamp. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, which is not clang.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Avoid name clash with the C++ standard header <mutex> by placing executables in a subdir.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(condition_variable examples/condition_variable.cpp)