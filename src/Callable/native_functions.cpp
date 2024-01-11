#include <chrono>
#include <string>
#include <vector>

#include "Variant/neem_value.hpp"
#include "Visitor/interpreter.hpp"
#include "Callable/native_functions.hpp"

//=Clock=======================================================================
int Clock::arity() {
  return 0;
}

Neem_value Clock::call(Interpreter& interpreter,
                       std::vector<Neem_value> arguments) {
  auto time = std::chrono::system_clock::now();
  auto since_epoch = time.time_since_epoch();
  auto milis =
    std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
  double now = milis.count();
  return Neem_value {Value_type::NUMBER, now};
}

std::string Clock::to_string() {
  return "<native fn>";
}
//=Clock=======================================================================

//=Str=========================================================================
int Str::arity() {
  return 1;
}

Neem_value Str::call(Interpreter&,
                     std::vector<Neem_value> arguments) {
  return Neem_value {Value_type::STRING, arguments[0].to_string()};
}

std::string Str::to_string() {
  return "<native fn>";
}
//=Str=========================================================================
