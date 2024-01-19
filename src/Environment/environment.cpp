#include <iostream>
#include <memory>
#include <string>

#include "Error/neem_runtime_error.hpp"
#include "Token/token.hpp"
#include "Variant/neem_value.hpp"
#include "environment.hpp"

Environment::Environment(Environment* p_enclosing):
    enclosing {p_enclosing} { }

void Environment::define(const std::string& name, const Neem_value& value) {
  values[name] = value;
}

Neem_value Environment::get(Token& name) {
  Value_map::iterator itr = values.find(name.lexeme);
  if (itr != values.end()) {
    return itr->second;
  }
  if (enclosing) {
    return enclosing->get(name);
  }
  throw Neem_runtime_error {name, "Undefined variable '" + name.lexeme + "'."};
}

Neem_value Environment::get_at(int distance, const std::string& name) {
  Value_map& values = ancestor(distance).values;
  Value_map::iterator itr = values.find(name);
  if (itr != values.end()) {
    return itr->second;
  }
  return Neem_value {};
}

Environment& Environment::ancestor(int distance) {
  Environment* environment {this};
  for (int i = 0; i < distance; i++) {
    environment = environment->enclosing;
  }
  return *environment;
}

void Environment::assign(Token& name, Neem_value& value) {
  Value_map::iterator itr = values.find(name.lexeme);
  if (itr != values.end()) {
    itr->second = value;
    return;
  }
  if (enclosing) {
    enclosing->assign(name, value);
    return;
  }
  throw Neem_runtime_error {name, "Undefined variable '" + name.lexeme + "'."};
}


void Environment::assign_at(int distance, Token& name, Neem_value& value) {
  Value_map& values = ancestor(distance).values;
  values[name.lexeme] = value;
}
