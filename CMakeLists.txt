cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(neem LANGUAGES CXX)

message("[Info]: CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message("[Info]: CMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}")
message("[Info]: CMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}")

add_library(expr OBJECT
  src/Token/token.hpp
  src/Variant/literal.hpp
  src/Visitor/mutable_state_visitor.hpp
  src/Ast/expr.hpp
  src/Ast/expr.cpp)

add_library(stmt OBJECT
  src/Ast/expr.hpp
  src/Visitor/mutable_state_visitor.hpp
  src/Ast/stmt.hpp
  src/Ast/stmt.cpp)

add_library(interpreter_error_reporter OBJECT
  src/common.hpp
  src/Error/neem_runtime_error.hpp
  src/Error/interpreter_error_reporter.hpp
  src/Error/interpreter_error_reporter.cpp)

add_library(lexer_error_reporter OBJECT
  src/common.hpp
  src/Error/lexer_error_reporter.hpp
  src/Error/lexer_error_reporter.cpp)

add_library(neem_runtime_error OBJECT
  src/Token/token.hpp
  src/Error/neem_runtime_error.hpp
  src/Error/neem_runtime_error.cpp)

add_library(parse_error OBJECT
  src/Error/parse_error.hpp
  src/Error/parse_error.cpp)

add_library(parser_error_reporter OBJECT
  src/common.hpp
  src/Error/parser_error_reporter.hpp
  src/Error/parser_error_reporter.cpp)

add_library(lexer OBJECT
  src/common.hpp
  src/Lexer/lexer.hpp
  src/Token/token.hpp
  src/Token/token_type.hpp
  src/Error/error_reporter.hpp
  src/Variant/literal.hpp
  src/Lexer/lexer.cpp)

add_library(parser OBJECT
  src/Token/token.hpp
  src/Ast/expr.hpp
  src/Parser/parser.hpp
  src/Parser/parser.cpp)

add_library(token OBJECT
  src/common.hpp
  src/Token/token.hpp
  src/Token/token_type.hpp
  src/Variant/literal.hpp
  src/Token/token.cpp)

add_library(literal OBJECT
  src/Variant/literal.hpp
  src/Variant/literal.cpp)

add_library(neem_value OBJECT
  src/Variant/neem_value.hpp
  src/Variant/neem_value.cpp)

add_library(ast_printer OBJECT
  src/Ast/expr.hpp
  src/Visitor/ast_printer.hpp
  src/Visitor/ast_printer.cpp)

add_library(interpreter OBJECT
  src/Ast/expr.hpp
  src/Ast/stmt.hpp
  src/Error/neem_runtime_error.hpp
  src/Error/interpreter_error_reporter.hpp
  src/common.hpp
  src/Visitor/interpreter.hpp
  src/Visitor/interpreter.cpp)

add_library(environment OBJECT
  src/Error/neem_runtime_error.hpp
  src/Token/token.hpp
  src/Environment/environment.hpp
  src/Environment/environment.cpp)

add_executable(neem src/neem.cpp)

target_link_libraries(neem expr interpreter_error_reporter lexer_error_reporter
  neem_runtime_error parse_error parser_error_reporter lexer parser token
  literal neem_value interpreter stmt environment)

