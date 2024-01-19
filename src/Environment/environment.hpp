#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <string>
#include <unordered_map>

#include "Token/token.hpp"
#include "Variant/neem_value.hpp"

class Environment {
public:
  Environment() = default;
  Environment(Environment*);
  void define(const std::string&, const Neem_value&);
  Neem_value get(Token&);
  Neem_value get_at(int, const std::string&);
  void assign(Token& token, Neem_value&);
  void assign_at(int, Token&, Neem_value&);
  using Value_map = std::unordered_map<std::string, Neem_value>;
private:
  Environment* enclosing {nullptr};
  Value_map values {};
  Environment& ancestor(int);
};

#endif // !ENVIRONMENT_H
