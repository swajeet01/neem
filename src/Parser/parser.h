#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "../Token/token.h"

class Parser {
  std::vector<Token> tokens;

public:
  Parser(const std::vector<Token>);
  void parse();
};

#endif // !PARSER_H
