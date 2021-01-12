cmake_minimum_required(VERSION 3.10)
project(fsdraw)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME cells)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG    "-g  -Wall -Wextra -Werror -pedantic")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_subdirectory(src)

