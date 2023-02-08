cmake_minimum_required(VERSION 3.22)
project(BFInterpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(BFInterpreter main.cpp Interpreter/interpreter.cpp Interpreter/interpreter.h Compiler/compiler.cpp Compiler/compiler.h)
