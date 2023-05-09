#ifndef LITERAL_H
#define LITERAL_H

#include <string>

enum class Literal_type { Number, String, Bool, Nil, None };

class Literal {
  Literal_type type {Literal_type::None};
  double num;
  std::string str;
  bool b00l;
public:
  Literal();
  Literal(Literal_type, double);
  Literal(Literal_type, std::string);
  Literal(Literal_type, bool);
  Literal(Literal_type);
  Literal_type get_type();
  std::string get_string();
  double get_number();
  bool get_bool();
  void put_string(std::string);
  void put_number(double);
  void put_bool(bool);
  std::string to_string();
};

#endif // !LITERAL_H
