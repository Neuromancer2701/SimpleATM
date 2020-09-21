cmake_minimum_required(VERSION 3.16)
project(SimpleATM)

set(CMAKE_CXX_STANDARD 20)

find_package (SQLite3)
find_package(fmt)
include_directories(${SQLite3_INCLUDE_DIRS} src)

link_directories(/usr/lib)

add_library(SimpleATM SHARED src/ATMapi.cpp src/ATMapi.h src/database.h src/database.cpp)

add_executable(tests tests/main.cpp)

target_link_libraries(tests SimpleATM sqlite3 fmt::fmt )


