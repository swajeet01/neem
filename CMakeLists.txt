cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(neem LANGUAGES CXX)

add_library(expr OBJECT
  src/Token/token.h
  src/Variant/literal.h
  src/Visitor/mutable_state_visitor.h
  src/Ast/expr.h
  src/Ast/expr.cpp)

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
  src/Variant/literal.h
  src/Lexer/lexer.cpp)

add_library(literal OBJECT
  src/Variant/literal.h
  src/Variant/literal.cpp)

add_library(token OBJECT
  src/common.h
  src/Token/token.h
  src/Token/token_type.h
  src/Variant/literal.h
  src/Token/token.cpp)

add_library(ast_printer OBJECT
  src/Ast/expr.h
  src/Visitor/ast_printer.h
  src/Visitor/ast_printer.cpp)

add_executable(neem src/neem.cpp)

target_link_libraries(neem expr literal lexer_error_reporter lexer token ast_printer)
