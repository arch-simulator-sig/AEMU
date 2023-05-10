file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)
add_executable(${PROJECT_NAME} ${SOURCES})