#include <chrono>
#include <vector>

#include "Callable/native_functions.hpp"
#include "Variant/neem_value.hpp"
#include "Visitor/interpreter.hpp"

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
