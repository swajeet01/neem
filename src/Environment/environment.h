#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>

#include "../Token/token.h"
#include "../Variant/neem_value.h"

class Environment {
  std::unordered_map<std::string, Neem_value> values;
public:
  void define(std::string&, Neem_value&);
  Neem_value get(Token&);
  void assign(Token& token, Neem_value&);
};

#endif // !ENVIRONMENT_H
