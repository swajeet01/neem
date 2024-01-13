#ifndef NEEM_VALUE_H
#define NEEM_VALUE_H

#include <memory>
#include <string>
#include <variant>

class Neem_callable;

enum class Value_type {NUMBER, STRING, BOOL, NEEM_CALLABLE, NIL};

class Neem_value {
  Value_type type {Value_type::NIL};
  
  double num { };
  bool b00l { };
  std::string str { };
  std::shared_ptr<Neem_callable> clb { };

  void clear_all();
public:
  Neem_value();
  Neem_value(Value_type, double);
  Neem_value(Value_type, std::string);
  Neem_value(Value_type, bool);
  Neem_value(Value_type, std::shared_ptr<Neem_callable>);

  Value_type get_type();
  std::string get_string();
  double get_number();
  bool get_bool();
  std::shared_ptr<Neem_callable> get_callable();
  void put_string(std::string);
void put_number(double);
  void put_bool(bool);
  void put_callable(std::shared_ptr<Neem_callable>);
  std::string to_string();
};

#endif // !NEEM_VALUE_H
