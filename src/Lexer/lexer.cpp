#include <cctype>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common.hpp"
#include "Token/token.hpp"
#include "Token/token_type.hpp"
#include "Variant/literal.hpp"
#include "lexer.hpp"

static const std::unordered_map<std::string, Token_type> keywords {
  {"let", Token_type::LET},
  {"true", Token_type::NTRUE},
  {"false", Token_type::NFALSE},
  {"and", Token_type::AND},
  {"or", Token_type::OR},
  {"if", Token_type::IF},
  {"else", Token_type::ELSE},
  {"fn", Token_type::FN},
  {"while", Token_type::WHILE},
  {"for", Token_type::FOR},
  {"in", Token_type::IN},
  {"struct", Token_type::STRUCT},
  {"this", Token_type::THIS},
  {"break", Token_type::BREAK},
  {"continue", Token_type::CONTINUE},
  {"return", Token_type::RETURN},
  {"nil", Token_type::NIL},
  {"print", Token_type::PRINT}
};

Lexer::Lexer(std::string  psource,
            Lexer_error_reporter& perror_reporter):
    source {std::move(psource)},
    error_reporter {perror_reporter} {}

inline bool Lexer::is_at_end() {
  return current >= source.size();
}

char Lexer::advance() {
  current++;
  return source[current - 1];
}

void Lexer::add_token(Token_type type) {
  add_token(type, Literal());
}

void Lexer::add_token(Token_type type, const Literal& literal) {
  auto lexeme = source.substr(start, current - start); // Already 1 char ahead.
  tokens.emplace_back(lexeme, line, type, literal);
}

char Lexer::peek() {
  if (is_at_end()) return '\0';
  return source[current];
}

char Lexer::peek_next() {
  if (current + 1 >= source.size()) return '\0';
  return source[current + 1];
}

bool Lexer::match(char expected) {
  if (is_at_end()) return false;
  if (source[current] != expected) return false;
  current++;
  return true;
}

void Lexer::string_tk() {
  while (peek() != '"' && !is_at_end()) {
    // Allow multiline strings
    if (peek() == '\n') line++;
    
    // if (peek() == '\n') {
    //  error_reporter->error(line, "Unterminated string literal.");
    //  return;
    // }
    advance();
  }

  // If allowing multiline strings
  if (is_at_end()) {
    error_reporter.error(line, "Unterminated string literal.");
    return;
  } 

  // Closing ".
  advance();
  
  auto value = source.substr(start + 1, current - start - 2);
  // TODO: Implement escape sequences.
  Literal str_literal {Literal_type::STRING, value};
  add_token(Token_type::STRING, str_literal);
}

void Lexer::number() {
  while (isdigit(peek())) advance();
  
  if (peek() == '.' && isdigit(peek_next())) {
    // Consume '.'.
    advance();

    while (isdigit(peek())) advance();
  }
  auto str_rep = source.substr(start, current - start);
  auto value = std::stod(str_rep);
  // Literal num_literal {Literal_type::NUMBER, value};
  Literal num_literal {Literal_type::NUMBER, value};
  add_token(Token_type::NUMBER, num_literal);
}

void Lexer::identifier() {
  while (isalnum(peek()) || peek() == '_') advance();
  auto text {source.substr(start, current - start)};
  if (keywords.find(text) != keywords.end()) {
    add_token(keywords.at(text));
  } else {
    add_token(Token_type::IDENTIFIER);
  }
}

void Lexer::get_token() {
  char c = advance();
  switch (c) {
    // Single character tokens.
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

    // Two character tokens.
    case '!':
      add_token(match('=') ? Token_type::BANG_EQ : Token_type::BANG);
      break;
    case '=':
      add_token(match('=') ? Token_type::EQ_EQ : Token_type::EQ);
      break;
    case '>':
      add_token(match('=') ? Token_type::GREATER_EQ : Token_type::GREATER);
      break;
    case '<':
      add_token(match('=') ? Token_type::LESSER_EQ : Token_type::LESSER);
      break;
    
    // Multi character tokens.
    case '%':
      if (match('%')) {
        while (peek() != common::newl && !is_at_end()) advance();
      } else {
        add_token(Token_type::MOD);
      }
      break;
    
    // Whitespace.
    case ' ':
    case '\r':
    case '\t':
      // Ignore
      break;
    case '\n':
      line++;
      break;

    case '"': string_tk(); break;
    
    default:
      if (isdigit(c)) {
        number();
      } else if (isalpha(c)) {
        identifier();
      } else {
        error_reporter.error(line, "Unexpected character.");
      }
      break;
  }
}

std::vector<Token> Lexer::get_tokens() {
  while (!is_at_end()) {
    start = current;
    get_token();
  }
  tokens.emplace_back(std::string {"EOF"}, line, Token_type::NEOF,
      Literal());
  return tokens;
}
