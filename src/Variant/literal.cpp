#include <string>
#include <stdexcept>

#include "literal.h"

// TODO: Refactor later.

Literal::Literal():
  type {Literal_type::None} {}

Literal::Literal(Literal_type ptype, double pnum) {
  if (ptype != Literal_type::Number) {
      throw std::runtime_error {"Expected Literal_type 'Number'."};
  }
  type = ptype;
  num = pnum;
}

Literal::Literal(Literal_type ptype, std::string pstr) {
  if (ptype != Literal_type::Number) {
      throw std::runtime_error {"Expected Literal_type 'String'."};
  }
  type = ptype;
  str = pstr;
}

Literal::Literal(Literal_type ptype, bool p_bool) {
  if (ptype != Literal_type::Bool) {
      throw std::runtime_error {"Expected Literal_type 'Bool'."};
  }
  type = ptype;
  b00l = p_bool;
}

Literal::Literal(Literal_type ptype) {
  if (ptype != Literal_type::Nil) {
      throw std::runtime_error {"Expected Literal_type 'Nil'."};
  }
  type = ptype;
}
Literal_type Literal::get_type() {
  return type;
}

std::string Literal::get_string() {
  if (type != Literal_type::String) {
    throw std::runtime_error
      {"Tried to retrive member 'str' while holding other type of value."};
  }
  return str;
}

double Literal::get_number() {
  if (type != Literal_type::Number) {
    throw std::runtime_error
      {"Tried to retrive member 'num' while holding other type of value."};
  }
  return num;
}

bool Literal::get_bool() {
  if (type != Literal_type::Bool) {
    throw std::runtime_error
      {"Tried to retrive member 'bool' while holding other type of value."};
  }
  return b00l;
}

void Literal::put_string(std::string data) {
  type = Literal_type::String;
  str = data;
}

void Literal::put_number(double data) {
  type = Literal_type::Number;
  num = data;
}

void Literal::put_bool(bool p_b00l) {
  type = Literal_type::Bool;
  b00l = p_b00l;
}

std::string Literal::to_string() {
  if (type == Literal_type::Nil) return "nil";
  if (type == Literal_type::Number) return std::to_string(num);
  if (type == Literal_type::String) return str;
  if (type == Literal_type::Bool) return b00l ? "true" : "false";
  return "<No Type>";
}
