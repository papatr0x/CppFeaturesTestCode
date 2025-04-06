# (c) 2025 Patricio Palma (ppalma.dev AT protonmail.com)
cmake_minimum_required(VERSION 3.20)
project(CppFeaturesTestCode)

set(CMAKE_CXX_STANDARD 23)

add_executable(CppFeaturesTestCode src/main.cpp)
add_compile_options(-Wall -Wextra -pedantic -Werror)
