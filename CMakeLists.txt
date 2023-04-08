cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(neem LANGUAGES CXX)

add_library(lexer STATIC src/Token/token.h src/Token/token_type.h
  src/Lexer/lexer.h src/Lexer/lexer.cpp)

add_library(token STATIC src/Token/token.h src/Token/token_type.h
  src/Token/token.cpp)

add_executable(neem src/neem.cpp)

target_link_libraries(neem lexer token)
