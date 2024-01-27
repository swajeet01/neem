#ifndef LITERAL_H
#define LITERAL_H

#include <string>
#include <variant>


enum class Literal_type { NUMBER, STRING, BOOL, NIL, NONE };

class Literal {
  Literal_type type;
  std::variant<double, bool, std::string, std::monostate> data;
  void clear_all();
public:
  Literal();
  Literal(Literal_type, double);
  Literal(Literal_type, const std::string&);
  Literal(Literal_type, bool);
  explicit Literal(Literal_type);
  Literal_type get_type();
  std::string get_string();
  double get_number();
  bool get_bool();
  void put_string(const std::string&);
  void put_number(double);
  void put_bool(bool);
  std::string to_string();
};

#endif // !LITERAL_H
