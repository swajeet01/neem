#include <memory>
#include <string>

#include "Error/neem_runtime_error.hpp"
#include "Token/token.hpp"
#include "Variant/neem_value.hpp"
#include "environment.hpp"

Environment::Environment(std::shared_ptr<Environment> p_enclosing):
    enclosing {p_enclosing} { }

void Environment::define(const std::string& name, const Neem_value& value) {
  values[name] = value;
}

Neem_value Environment::get(Token& name) {
  if (values.find(name.lexeme) != values.end()) {
    return values[name.lexeme];
  }
  if (enclosing) {
    return enclosing->get(name);
  }
  throw Neem_runtime_error {name, "Undefined variable '" + name.lexeme + "'."};
}

void Environment::assign(Token& name, Neem_value& value) {
  if (values.find(name.lexeme) != values.end()) {
    values[name.lexeme] = value;
    return;
  }
  if (enclosing) {
    enclosing->assign(name, value);
    return;
  }
  throw Neem_runtime_error {name, "Undefined variable '" + name.lexeme + "'."};
}
