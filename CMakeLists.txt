cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(neem LANGUAGES CXX)

message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

add_library(expr OBJECT)
add_library(stmt OBJECT)
add_library(interpreter_error_reporter OBJECT)
add_library(lexer_error_reporter OBJECT)
add_library(neem_runtime_error OBJECT)
add_library(parse_error OBJECT)
add_library(parser_error_reporter OBJECT)
add_library(lexer OBJECT)
add_library(parser OBJECT)
add_library(token OBJECT)
add_library(literal OBJECT)
add_library(neem_value OBJECT)
add_library(ast_printer OBJECT)
add_library(interpreter OBJECT)
add_library(environment OBJECT)

add_executable(neem src/neem.cpp)

target_sources(expr
  PRIVATE
  src/Token/token.hpp
  src/Variant/literal.hpp
  src/Visitor/mutable_state_visitor.hpp
  src/Ast/expr.hpp
  src/Ast/expr.cpp
)

target_sources(stmt
  PRIVATE
  src/Ast/expr.hpp
  src/Visitor/mutable_state_visitor.hpp
  src/Ast/stmt.hpp
  src/Ast/stmt.cpp
)

target_sources(interpreter_error_reporter
  PRIVATE
  src/common.hpp
  src/Error/neem_runtime_error.hpp
  src/Error/interpreter_error_reporter.hpp
  src/Error/interpreter_error_reporter.cpp
)

target_sources(lexer_error_reporter
  PRIVATE
  src/common.hpp
  src/Error/lexer_error_reporter.hpp
  src/Error/lexer_error_reporter.cpp
)

target_sources(neem_runtime_error
  PRIVATE
  src/Token/token.hpp
  src/Error/neem_runtime_error.hpp
  src/Error/neem_runtime_error.cpp
)

target_sources(parse_error
  PRIVATE
  src/Error/parse_error.hpp
  src/Error/parse_error.cpp
)

target_sources(parser_error_reporter
  PRIVATE
  src/common.hpp
  src/Error/parser_error_reporter.hpp
  src/Error/parser_error_reporter.cpp
)

target_sources(lexer
  PRIVATE
  src/common.hpp
  src/Lexer/lexer.hpp
  src/Token/token.hpp
  src/Token/token_type.hpp
  src/Error/error_reporter.hpp
  src/Variant/literal.hpp
  src/Lexer/lexer.cpp
)

target_sources(parser
  PRIVATE
  src/Token/token.hpp
  src/Ast/expr.hpp
  src/Parser/parser.hpp
  src/Parser/parser.cpp
)

target_sources(token
  PRIVATE
  src/common.hpp
  src/Token/token.hpp
  src/Token/token_type.hpp
  src/Variant/literal.hpp
  src/Token/token.cpp
)

target_sources(literal
  PRIVATE
  src/Variant/literal.hpp
  src/Variant/literal.cpp
)

target_sources(neem_value
  PRIVATE
  src/Variant/neem_value.hpp
  src/Variant/neem_value.cpp
)

target_sources(ast_printer
  PRIVATE
  src/Ast/expr.hpp
  src/Visitor/ast_printer.hpp
  src/Visitor/ast_printer.cpp
)

target_sources(interpreter
  PRIVATE
  src/Ast/expr.hpp
  src/Ast/stmt.hpp
  src/Error/neem_runtime_error.hpp
  src/Error/interpreter_error_reporter.hpp
  src/common.hpp
  src/Visitor/interpreter.hpp
  src/Visitor/interpreter.cpp
)

target_sources(environment
  PRIVATE
  src/Error/neem_runtime_error.hpp
  src/Token/token.hpp
  src/Environment/environment.hpp
  src/Environment/environment.cpp
)


target_link_libraries(neem
  PRIVATE
  expr
  interpreter_error_reporter
  lexer_error_reporter
  neem_runtime_error
  parse_error
  parser_error_reporter
  lexer parser token
  literal
  neem_value
  interpreter
  stmt
  environment
)
