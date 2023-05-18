#include <string>
#include <stdexcept>

#include "neem_value.h"

Neem_value::Neem_value() {}

Neem_value::Neem_value(Value_type ptype, double pnum) {
  if (ptype != Value_type::NUMBER) {
    throw std::runtime_error {"Expected Value_type 'NUMBER'."};
  }
  type = ptype;
  num = pnum;
}

Neem_value::Neem_value(Value_type ptype, std::string pstr) {
  if (ptype != Value_type::STRING) {
    throw std::runtime_error {"Expected Value_type 'STRING'."};
  }
  type = ptype;
  str = pstr;
}


Neem_value::Neem_value(Value_type ptype, bool pbool) {
  if (ptype != Value_type::BOOL) {
      throw std::runtime_error {"Expected Value_type 'BOOL'."};
  }
  type = ptype;
  b00l = pbool;
}

Value_type Neem_value::get_type() {
  return type;
}

std::string Neem_value::get_string() {
  if (type != Value_type::STRING) {
    throw std::runtime_error
      {"Tried to retrive member 'str' while holding other type of value."};
  }
  return str;
}

double Neem_value::get_number() {
  if (type != Value_type::NUMBER) {
    throw std::runtime_error
      {"Tried to retrive member 'num' while holding other type of value."};
  }
  return num;
}

bool Neem_value::get_bool() {
  if (type != Value_type::BOOL) {
    throw std::runtime_error
      {"Tried to retrive member 'bool' while holding other type of value."};
  }
  return b00l;
}

void Neem_value::put_string(std::string data) {
  type = Value_type::STRING;
  str = data;
}

void Neem_value::put_number(double data) {
  type = Value_type::NUMBER;
  num = data;
}

void Neem_value::put_bool(bool p_b00l) {
  type = Value_type::BOOL;
  b00l = p_b00l;
}

std::string Neem_value::to_string() {
  if (type == Value_type::NIL) return "nil";
  if (type == Value_type::NUMBER) return std::to_string(num);
  if (type == Value_type::STRING) return str;
  if (type == Value_type::BOOL) return b00l ? "true" : "false";
  return "undefined";
}
