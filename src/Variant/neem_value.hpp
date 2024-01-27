#ifndef NEEM_VALUE_H
#define NEEM_VALUE_H

#include <memory>
#include <string>
#include <variant>

class Neem_callable;

enum class Value_type {NUMBER, STRING, BOOL, NEEM_CALLABLE, NIL};

class Neem_value {
  Value_type type;
  std::variant<double, bool, std::string, std::shared_ptr<Neem_callable>, std::monostate> data;
  void clear_all();
public:
  Neem_value();
  Neem_value(Value_type, double);
  Neem_value(Value_type, const std::string&);
  Neem_value(Value_type, bool);
  Neem_value(Value_type, const std::shared_ptr<Neem_callable>&);

  Value_type get_type();
  std::string get_string();
  double get_number();
  bool get_bool();
  std::shared_ptr<Neem_callable> get_callable();
  void put_string(const std::string&);
  void put_number(double);
  void put_bool(bool);
  void put_callable(const std::shared_ptr<Neem_callable>&);
  std::string to_string();
};

#endif // !NEEM_VALUE_H
