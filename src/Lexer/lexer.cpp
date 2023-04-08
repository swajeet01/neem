#include <string>
#include <vector>
#include <memory>

#include "../common.h"
#include "lexer.h"
#include "../Token/token.h"
#include "../Token/token_type.h"
#include "../Error/error_reporter.h"

Lexer::Lexer(const std::string psource,
    std::shared_ptr<Error_reporter> perror_reporter):
    source {psource},
    error_reporter {perror_reporter} {}

inline bool Lexer::is_at_end() {
  return current >= source.size();
}

char Lexer::advance() {
  current++;
  return source[current - 1];
}

void Lexer::add_token(Token_type type) {
  add_token(type, 0);
}

void Lexer::add_token(Token_type type, int) {
  auto lexeme = source.substr(start, current - start); // Already 1 char ahead.
  tokens.push_back(Token(lexeme, line, type));
}

char Lexer::peek() {
  if (is_at_end()) return common::null;
  return source[current];
}

bool Lexer::match(char expected) {
  if (is_at_end()) return false;
  if (source[current] != expected) return false;
  current++;
  return true;
}

void Lexer::get_token() {
  char c = advance();
  switch (c) {
    case '{': add_token(Token_type::LEFT_BRACE); break;
    case '}': add_token(Token_type::RIGHT_BRACE); break;
    case '(': add_token(Token_type::LEFT_PAREN); break;
    case ')': add_token(Token_type::RIGHT_PAREN); break;
    case '[': add_token(Token_type::LEFT_BRACK); break;
    case ']': add_token(Token_type::RIGHT_BRACK); break;
    case ',': add_token(Token_type::COMMA); break;
    case '.': add_token(Token_type::DOT); break;
    case '-': add_token(Token_type::MINUS); break;
    case '+': add_token(Token_type::PLUS); break;
    case '/': add_token(Token_type::SLASH); break;
    case '*': add_token(Token_type::STAR); break;
    case ';': add_token(Token_type::SEMI_COL); break;
    case '!':
      add_token(match('=') ? Token_type::BANG_EQ : Token_type::BANG);
      break;
    case '=':
      add_token(match('=') ? Token_type::EQ_EQ : Token_type::EQ);
      break;
    case '<':
      add_token(match('=') ? Token_type::GREATER_EQ : Token_type::GREATER);
      break;
    case '>':
      add_token(match('=') ? Token_type::LESSER_EQ : Token_type::LESSER);
      break;
    case '%':
      if (match('%')) {
        while (peek() != common::newl && !is_at_end()) advance();
      } else {
        add_token(Token_type::MOD);
      }
      break;
    default:
      error_reporter->error(line, "Unexpected character.");
      break;
  }
}

std::vector<Token> Lexer::get_tokens() {
  while (!is_at_end()) {
    start = current;
    get_token();
  }
  tokens.push_back(Token(std::string {"EOF"}, line, Token_type::NEOF));
  return tokens;
}
