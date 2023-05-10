project(AEMU_LIB)
file(GLOB_RECURSE AEMU_LIB_SOURCES "src/*.cpp")
add_library(AEMU_LIB ${AEMU_LIB_SOURCES})
include_directories(include)