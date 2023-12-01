# CMakeList.txt : CMake project for advent2023, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (day01pt1 "pt1.c")
add_executable (day01pt2 "pt2.c")

target_include_directories (day01pt1 PRIVATE "../../include/")
target_link_directories (day01pt1 PRIVATE advent2023)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET advent2023 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
