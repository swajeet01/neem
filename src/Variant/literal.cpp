#include <string>
#include <stdexcept>

#include "literal.h"

// TODO: Refactor later.

Literal::Literal():
  type {Literal_type::None} {}

Literal::Literal(Literal_type ptype, double pnum) {
  if (ptype == Literal_type::String) {
      throw std::runtime_error {"Expected Literal_type 'Number', got 'String'"};
  }
  type = ptype;
  num = pnum;
}

Literal::Literal(Literal_type ptype, std::string pstr) {
  if (ptype == Literal_type::Number) {
      throw std::runtime_error {"Expected Literal_type 'String', got 'Number'"};
  }
  type = ptype;
  str = pstr;
}

Literal_type Literal::get_type() {
  return type;
}

std::string Literal::get_string() {
  if (type == Literal_type::None) {
    throw std::runtime_error {"Tried to retrive member 'str' while holding <None>"};
  }
  if (type == Literal_type::Number) {
      throw std::runtime_error {"Tried to retrive member 'str' while holding 'num'"};
  }
  return str;
}

double Literal::get_number() {
  if (type == Literal_type::None) {
    throw std::runtime_error {"Tried to retrive member 'num' while holding <None>"};
  }
  if (type == Literal_type::String) {
      throw std::runtime_error {"Tried to retrive member 'num' while holding 'str'"};
  }
  return num;
}

void Literal::put_string(std::string data) {
  type = Literal_type::String;
  str = data;
}

void Literal::put_number(double data) {
  type = Literal_type::Number;
  num = data;
}

std::string Literal::to_string() {
  switch (type) {
    case Literal_type::None:
      return "nil";
      break; // lol
    case Literal_type::Number:
      return std::to_string(num);
      break;
    case Literal_type::String:
      return str;
      break;
    default:
      return "";
      break;
  }
}
