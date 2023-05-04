#ifndef LITERAL_H
#define LITERAL_H

#include <string>

enum class Literal_type { Number, String, None };

class Literal {
  Literal_type type {Literal_type::None};
  double num;
  std::string str;
public:
  Literal();
  Literal(Literal_type, double);
  Literal(Literal_type, std::string);
  Literal_type get_type();
  std::string get_string();
  double get_number();
  void put_string(std::string);
  void put_number(double);
  std::string to_string();
};

#endif // !LITERAL_H
