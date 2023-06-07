#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <string>
#include <unordered_map>

#include "../Token/token.hpp"
#include "../Variant/neem_value.hpp"

class Environment {
  std::shared_ptr<Environment> enclosing;
  std::unordered_map<std::string, Neem_value> values;
public:
  Environment() = default;
  Environment(std::shared_ptr<Environment>);
  void define(std::string&, Neem_value&);
  Neem_value get(Token&);
  void assign(Token& token, Neem_value&);
};

#endif // !ENVIRONMENT_H
