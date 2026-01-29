cmake_minimum_required(VERSION 3.25)
project(some_game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SRCS})

include(Dependencies.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE
  src
)

include(Test.cmake)