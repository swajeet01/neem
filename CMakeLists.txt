cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(neem LANGUAGES CXX)

add_library(expr OBJECT
  src/Token/token.h
  src/Variant/literal.h
  src/Visitor/mutable_state_visitor.h
  src/Ast/expr.h
  src/Ast/expr.cpp)

add_library(interpreter_error_reporter OBJECT
  src/common.h
  src/Error/neem_runtime_error.h
  src/Error/interpreter_error_reporter.h
  src/Error/interpreter_error_reporter.cpp)

add_library(lexer_error_reporter OBJECT
  src/common.h
  src/Error/lexer_error_reporter.h
  src/Error/lexer_error_reporter.cpp)

add_library(neem_runtime_error OBJECT
  src/Token/token.h
  src/Error/neem_runtime_error.h
  src/Error/neem_runtime_error.cpp)

add_library(parse_error OBJECT
  src/Error/parse_error.h
  src/Error/parse_error.cpp)

add_library(parser_error_reporter OBJECT
  src/common.h
  src/Error/parser_error_reporter.h
  src/Error/parser_error_reporter.cpp)

add_library(lexer OBJECT
  src/common.h
  src/Lexer/lexer.h
  src/Token/token.h
  src/Token/token_type.h
  src/Error/error_reporter.h
  src/Variant/literal.h
  src/Lexer/lexer.cpp)

add_library(parser OBJECT
  src/Token/token.h
  src/Ast/expr.h
  src/Parser/parser.h
  src/Parser/parser.cpp)

add_library(token OBJECT
  src/common.h
  src/Token/token.h
  src/Token/token_type.h
  src/Variant/literal.h
  src/Token/token.cpp)

add_library(literal OBJECT
  src/Variant/literal.h
  src/Variant/literal.cpp)

add_library(neem_value OBJECT
  src/Variant/neem_value.h
  src/Variant/neem_value.cpp)

add_library(ast_printer OBJECT
  src/Ast/expr.h
  src/Visitor/ast_printer.h
  src/Visitor/ast_printer.cpp)

add_library(interpreter OBJECT
  src/Ast/expr.h
  src/Error/neem_runtime_error.h
  src/Error/interpreter_error_reporter.h
  src/common.h
  src/Visitor/interpreter.h
  src/Visitor/interpreter.cpp)

add_executable(neem src/neem.cpp)

target_link_libraries(neem expr interpreter_error_reporter lexer_error_reporter
  neem_runtime_error parse_error parser_error_reporter lexer parser token
  literal neem_value interpreter)

