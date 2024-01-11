#ifndef NEEM_FUNCTION_H
#define NEEM_FUNCTION_H

#include "Ast/stmt.hpp"
#include "Callable/neem_callable.hpp"
#include <memory>
#include <string>

class Neem_function: public Neem_callable {
  std::shared_ptr<Function> declaration;
  std::string repr {"<fn ?>"};
public:
  Neem_function(std::shared_ptr<Function>);
  int arity() override;
  Neem_value call(Interpreter &, std::vector<Neem_value>) override;
  std::string to_string() override;
};

#endif // !NEEM_FUNCTION_H
