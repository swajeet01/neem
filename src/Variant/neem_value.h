#ifndef NEEM_VALUE_H
#define NEEM_VALUE_H

#include <string>
#include <variant>

enum class Value_type {NUMBER, STRING, BOOL, NIL};

class Neem_nil {};

class Neem_value {
  Value_type type;

  //  double num;
  //  std::string str;
  //  bool b00l;

  std::variant<double, bool, std::string, Neem_nil> data;

  void clear_all();
public:
  Neem_value();
  Neem_value(Value_type, double);
  Neem_value(Value_type, std::string);
  Neem_value(Value_type, bool);

  Value_type get_type();
  std::string get_string();
  double get_number();
  bool get_bool();
  void put_string(std::string);
  void put_number(double);
  void put_bool(bool);
  std::string to_string();
};

#endif // !NEEM_VALUE_H
