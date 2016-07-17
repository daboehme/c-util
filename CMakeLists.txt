#
# c-util
#

project (c-util C CXX)
cmake_minimum_required(VERSION 3.0)

set(C_UTIL_VERSION "1.1")

#
# Set C99 Flags
#

if (${CMAKE_C_COMPILER_ID} MATCHES Intel)
  # CMake does not have proper compiler feature support for Intel compilers :-/
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
else()
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_STANDARD 99)
endif()

#
# Subdirectories
#

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)

