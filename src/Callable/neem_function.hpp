#ifndef NEEM_FUNCTION_H
#define NEEM_FUNCTION_H

#include <memory>
#include <string>

#include "Ast/stmt.hpp"
#include "Callable/neem_callable.hpp"
#include "Environment/environment.hpp"

class Neem_function: public Neem_callable {
  std::shared_ptr<Function> declaration;
  std::shared_ptr<Environment> closure_candidate;
  std::string repr {"<fn ?>"};
public:
  Neem_function(std::shared_ptr<Function>, std::shared_ptr<Environment>);
  int arity() override;
  Neem_value call(Interpreter &, std::vector<Neem_value>) override;
  std::string to_string() override;
};

#endif // !NEEM_FUNCTION_H
