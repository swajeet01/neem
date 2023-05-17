#include <string>
#include <stdexcept>

#include "literal.h"

// TODO: Refactor later.

Literal::Literal():
  type {Literal_type::NONE} {}

Literal::Literal(Literal_type ptype, double pnum) {
  if (ptype != Literal_type::NUMBER) {
      throw std::runtime_error {"Expected Literal_type 'NUMBER'."};
  }
  type = ptype;
  num = pnum;
}

Literal::Literal(Literal_type ptype, std::string pstr) {
  if (ptype != Literal_type::NUMBER) {
      throw std::runtime_error {"Expected Literal_type 'STRING'."};
  }
  type = ptype;
  str = pstr;
}

Literal::Literal(Literal_type ptype, bool p_bool) {
  if (ptype != Literal_type::BOOL) {
      throw std::runtime_error {"Expected Literal_type 'BOOL'."};
  }
  type = ptype;
  b00l = p_bool;
}

Literal::Literal(Literal_type ptype) {
  if (ptype != Literal_type::NIL) {
      throw std::runtime_error {"Expected Literal_type 'NIL'."};
  }
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
  return str;
}

double Literal::get_number() {
  if (type != Literal_type::NUMBER) {
    throw std::runtime_error
      {"Tried to retrive member 'num' while holding other type of value."};
  }
  return num;
}

bool Literal::get_bool() {
  if (type != Literal_type::BOOL) {
    throw std::runtime_error
      {"Tried to retrive member 'bool' while holding other type of value."};
  }
  return b00l;
}

void Literal::put_string(std::string data) {
  type = Literal_type::STRING;
  str = data;
}

void Literal::put_number(double data) {
  type = Literal_type::NUMBER;
  num = data;
}

void Literal::put_bool(bool p_b00l) {
  type = Literal_type::BOOL;
  b00l = p_b00l;
}

std::string Literal::to_string() {
  if (type == Literal_type::NIL) return "nil";
  if (type == Literal_type::NUMBER) return std::to_string(num);
  if (type == Literal_type::STRING) return str;
  if (type == Literal_type::BOOL) return b00l ? "true" : "false";
  return "<No Type>";
}
