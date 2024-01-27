#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Ast/stmt.hpp"
#include "Environment/environment.hpp"
#include "Variant/neem_value.hpp"
#include "Visitor/interpreter.hpp"
#include "Callable/neem_function.hpp"

Neem_function::Neem_function(std::shared_ptr<Function> p_declaration,
                             std::shared_ptr<Environment> p_closure):
    declaration {std::move(p_declaration)},
    closure_candidate {std::move(p_closure)} {
  std::ostringstream name_composer;
  name_composer << "<fn " << declaration->name.lexeme << ">";
  repr = name_composer.str();
}

int Neem_function::arity() {
  return static_cast<int>(declaration->params.size());
}

Neem_value Neem_function::call(Interpreter& interpreter,
                    std::vector<Neem_value> arguments) {
  Environment* closure = closure_candidate ?
      closure_candidate.get() : &interpreter.globals;
  std::shared_ptr<Environment> environment = 
      std::make_shared<Environment>(closure);
  for (int i = 0; i < declaration->params.size(); i++) {
    environment->define(declaration->params[i].lexeme, arguments[i]);
  }
  try {
    interpreter.execute_block(declaration->body, environment);
  } catch (Return_hack& return_val) {
    return return_val.value;
  }
  return Neem_value {};
}

std::string Neem_function::to_string() {
  return repr;
}
