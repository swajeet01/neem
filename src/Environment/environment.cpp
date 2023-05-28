#include <string>

#include "../Error/neem_runtime_error.h"
#include "../Token/token.h"
#include "environment.h"

void Environment::define(std::string& name, Neem_value& value) {
  values[name] = value;
}

Neem_value Environment::get(Token& name) {
  if (values.find(name.lexeme) != values.end()) {
    return values[name.lexeme];
  }
  throw Neem_runtime_error {name, "Undefined variable '" + name.lexeme + "'."};
}

void Environment::assign(Token& name, Neem_value& value) {
  if (values.find(name.lexeme) != values.end()) {
    values[name.lexeme] = value;
    return;
  }
  throw Neem_runtime_error {name, "Undefined variable '" + name.lexeme + "'."};
}
