#ifndef NATIVE_FUNCTIONS_HPP
#define NATIVE_FUNCTIONS_HPP

#include <vector>

#include "Callable/neem_callable.hpp"

class Clock: public Neem_callable {
public:
  int arity() override;
  Neem_value call(Interpreter&, std::vector<Neem_value>) override;
  std::string to_string() override;
};

class Str: public Neem_callable {
public:
  int arity() override;
  Neem_value call(Interpreter&, std::vector<Neem_value>) override;
  std::string to_string() override;
};

class Read: public Neem_callable {
public:
  int arity() override;
  Neem_value call(Interpreter &, std::vector<Neem_value>) override;
  std::string to_string() override;
};

#endif // !NATIVE_FUNCTIONS_HPP
