#ifndef NEEM_VALUE_H
#define NEEM_VALUE_H

#include <string>

enum class Value_type {NUMBER, STRING, BOOL, NIL};

class Neem_value {
  Value_type type {Value_type::NIL};
  double num;
  std::string str;
  bool b00l;
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
