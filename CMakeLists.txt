cmake_minimum_required(VERSION 3.25)
project(some_game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(Dependencies.cmake)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE
  src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  raylib
)
