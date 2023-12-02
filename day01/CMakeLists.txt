# CMakeList.txt : CMake project for advent2023, include source and define
# project specific logic here.
#

# Add source to this project's executable.

include_directories("../include")
add_executable (day01pt1 "pt1.c")


target_link_libraries(day01pt1 advent2023)

add_executable (day01pt2 "pt2.c")
target_link_libraries(day01pt2 advent2023)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET advent2023 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
