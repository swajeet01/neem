
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "../Token/token.h"

class Parser {
  std::vector<Token> mtokens;

public:
  Parser(const std::vector<Token> tokens):
    mtokens {tokens} {}

  void parse();
};

#endif // !PARSER_H
