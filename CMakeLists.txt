cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project(AEMU CXX)

add_compile_options ( -Werror
  -Wall -Wextra -Winline -Winit-self -Wno-unused-function
  -Wuninitialized -Wno-sequence-point -Wno-inline -Wno-unknown-pragmas
  -Woverloaded-virtual -Wno-unused-parameter -Wno-missing-field-initializers -pipe)

# Use ccache if installed
find_program (CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  set_property (GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
  message ("-- Using ccache")
endif ()

# Profile build flags
set(CMAKE_CXX_FLAGS_PROFILE   "-O2 -pg -g -ftime-trace")
set(CMAKE_CXX_FLAGS_FASTDEBUG "-O2 -g")

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)
add_executable(${PROJECT_NAME} ${SOURCES})


# target_link_options    (${PROJECT_NAME} PUBLIC -flto)
# target_compile_options (${PROJECT_NAME} PUBLIC -flto)