﻿# CMakeList.txt : CMake project for advent2023, include source and define
# project specific logic here.
#

# Add source to this project's executable.

include_directories("../include")
add_library (advent2023 "advent2023.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET advent2023 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
