cmake_minimum_required(VERSION 3.17)
project(nml)

set(CMAKE_CXX_STANDARD 20)

add_executable(nml main.cpp Token.cpp Token.h Lexer.cpp Lexer.h)