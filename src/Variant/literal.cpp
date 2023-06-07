#include <string>
#include <stdexcept>
#include <variant>

#include "literal.hpp"

Literal::Literal() {
  data = std::monostate {};
  type = Literal_type::NONE;
}

Literal::Literal(Literal_type ptype, double pnum) {
  if (ptype != Literal_type::NUMBER) {
      throw std::runtime_error {"Expected Literal_type 'NUMBER'."};
  }
  type = ptype;
  data = pnum;
}

Literal::Literal(Literal_type ptype, std::string pstr) {
  if (ptype != Literal_type::STRING) {
      throw std::runtime_error {"Expected Literal_type 'STRING'."};
  }
  type = ptype;
  data = pstr;
}

Literal::Literal(Literal_type ptype, bool pbool) {
  if (ptype != Literal_type::BOOL) {
      throw std::runtime_error {"Expected Literal_type 'BOOL'."};
  }
  type = ptype;
  data = pbool;
}

Literal::Literal(Literal_type ptype) {
  if (ptype != Literal_type::NIL) {
      throw std::runtime_error {"Expected Literal_type 'NIL'."};
  }
  data = std::monostate {};
  type = ptype;
}

Literal_type Literal::get_type() {
  return type;
}

std::string Literal::get_string() {
  if (type != Literal_type::STRING) {
    throw std::runtime_error
      {"Tried to retrive member 'str' while holding other type of value."};
  }
  return std::get<std::string>(data);
}

double Literal::get_number() {
  if (type != Literal_type::NUMBER) {
    throw std::runtime_error
      {"Tried to retrive member 'num' while holding other type of value."};
  }
  return std::get<double>(data);
}

bool Literal::get_bool() {
  if (type != Literal_type::BOOL) {
    throw std::runtime_error
      {"Tried to retrive member 'bool' while holding other type of value."};
  }
  return std::get<bool>(data);
}

void Literal::put_string(std::string str) {
  type = Literal_type::STRING;
  data = str;
}

void Literal::put_number(double num) {
  type = Literal_type::NUMBER;
  data = num;
}

void Literal::put_bool(bool b00l) {
  type = Literal_type::BOOL;
  data = b00l;
}

std::string Literal::to_string() {
  if (type == Literal_type::NIL) return "nil";
  if (type == Literal_type::NUMBER) return std::to_string(get_number());
  if (type == Literal_type::STRING) return get_string();
  if (type == Literal_type::BOOL) return get_bool() ? "true" : "false";
  return "<No Type>";
}
