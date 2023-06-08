#include <string>
#include <stdexcept>
#include <variant>

#include "neem_value.hpp"

Neem_value::Neem_value() {
  data = std::monostate {};
  type = Value_type::NIL;
}

Neem_value::Neem_value(Value_type ptype, double pnum) {
  if (ptype != Value_type::NUMBER) {
    throw std::runtime_error {"[Internal] Expected Value_type 'NUMBER'."};
  }
  type = ptype;
  data = pnum;
}

Neem_value::Neem_value(Value_type ptype, std::string pstr) {
  if (ptype != Value_type::STRING) {
    throw std::runtime_error {"[Internal] Expected Value_type 'STRING'."};
  }
  type = ptype;
  data = pstr;
}


Neem_value::Neem_value(Value_type ptype, bool pbool) {
  if (ptype != Value_type::BOOL) {
      throw std::runtime_error {"[Internal] Expected Value_type 'BOOL'."};
  }
  type = ptype;
  data = pbool;
}

Value_type Neem_value::get_type() {
  return type;
}

std::string Neem_value::get_string() {
  if (type != Value_type::STRING) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'str' while holding other type of value."};
  }
  return std::get<std::string>(data);
}

double Neem_value::get_number() {
  if (type != Value_type::NUMBER) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'num' while holding other type of value."};
  }
  return std::get<double>(data);
}

bool Neem_value::get_bool() {
  if (type != Value_type::BOOL) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'bool' while holding other type of value."};
  }
  return std::get<bool>(data);
}

void Neem_value::put_string(std::string str) {
  type = Value_type::STRING;
  data = str;
}

void Neem_value::put_number(double num) {
  type = Value_type::NUMBER;
  data = num;
}

void Neem_value::put_bool(bool b00l) {
  type = Value_type::BOOL;
  data = b00l;
}

std::string Neem_value::to_string() {
  if (type == Value_type::NIL) return "nil";
  if (type == Value_type::NUMBER) return std::to_string(get_number());
  if (type == Value_type::STRING) return get_string();
  if (type == Value_type::BOOL) return get_bool() ? "true" : "false";
  // Unreachable
  return "undefined";
}
