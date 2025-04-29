cmake_minimum_required(VERSION 3.10)
project(Pasjans)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Główna aplikacja
add_executable(pasjans main.cpp pasjans.cpp)

# Testy
add_executable(testy test.cpp pasjans.cpp)

enable_testing()
add_test(NAME TestyPasjansa COMMAND testy)
