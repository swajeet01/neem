cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(neem LANGUAGES CXX)

add_library(lexer_error_reporter OBJECT
  src/common.h
  src/Error/lexer_error_reporter.h
  src/Error/lexer_error_reporter.cpp)

add_library(lexer OBJECT
  src/common.h
  src/Lexer/lexer.h
  src/Token/token.h
  src/Token/token_type.h
  src/Error/error_reporter.h
  src/Lexer/lexer.cpp)

add_library(token OBJECT
  src/common.h
  src/Token/token.h
  src/Token/token_type.h
  src/Token/token.cpp)

add_executable(neem src/neem.cpp)

target_link_libraries(neem lexer_error_reporter lexer token)
