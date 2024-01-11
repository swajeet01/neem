#ifndef NEEM_CALLABLE_H
#define NEEM_CALLABLE_H

#include <memory>
#include <string>
#include <vector>

class Interpreter;
class Neem_value;

class Neem_callable {
public:
  virtual int arity() = 0;
  virtual Neem_value call(Interpreter&,
                          std::vector<Neem_value>) = 0;
  virtual std::string to_string() = 0;
  ~Neem_callable() { }
};

#endif // !NEEM_CALLABLE_H
