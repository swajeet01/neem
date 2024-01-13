#include <memory>
#include <string>
#include <stdexcept>
#include <variant>

#include "Callable/neem_callable.hpp"
#include "nv_neem_value.hpp"

Neem_value::Neem_value() { }

Neem_value::Neem_value(Value_type ptype, double pnum) {
  if (ptype != Value_type::NUMBER) {
    throw std::runtime_error {"[Internal] Expected Value_type 'NUMBER'."};
  }
  type = ptype;
  num = pnum;
}

Neem_value::Neem_value(Value_type ptype, std::string pstr) {
  if (ptype != Value_type::STRING) {
    throw std::runtime_error {"[Internal] Expected Value_type 'STRING'."};
  }
  type = ptype;
  str = pstr;
}


Neem_value::Neem_value(Value_type ptype, bool pbool) {
  if (ptype != Value_type::BOOL) {
      throw std::runtime_error {"[Internal] Expected Value_type 'BOOL'."};
  }
  type = ptype;
  b00l = pbool;
}

Neem_value::Neem_value(Value_type ptype, std::shared_ptr<Neem_callable> callable) {
  if (ptype != Value_type::NEEM_CALLABLE) {
    throw std::runtime_error {"[Internal] Expected Value_type 'NEEM_CALLABLE'."};
  }
  type = ptype;
  clb = callable;
}

Value_type Neem_value::get_type() {
  return type;
}

std::string Neem_value::get_string() {
  if (type != Value_type::STRING) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'str' while holding other type of value."};
  }
  return str;
}

double Neem_value::get_number() {
  if (type != Value_type::NUMBER) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'num' while holding other type of value."};
  }
  return num;
}

bool Neem_value::get_bool() {
  if (type != Value_type::BOOL) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'bool' while holding other type of value."};
  }
  return b00l;
}

std::shared_ptr<Neem_callable> Neem_value::get_callable() {
  if (type != Value_type::NEEM_CALLABLE) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'callable' while holding other type of value."};
  }
  return clb;
}

void Neem_value::put_string(std::string data) {
  clear_all();
  type = Value_type::STRING;
  str = data;
}

void Neem_value::put_number(double data) {
  clear_all();
  type = Value_type::NUMBER;
  num = data;
}

void Neem_value::put_bool(bool data) {
  clear_all();
  type = Value_type::BOOL;
  b00l = data;
}

void Neem_value::put_callable(std::shared_ptr<Neem_callable> data) {
  clear_all();
  type = Value_type::NEEM_CALLABLE;
  clb = data;
}

void Neem_value::clear_all() {
  num = 0;
  b00l = false;
  str = "";
  clb.reset();
}

std::string Neem_value::to_string() {
  if (type == Value_type::NIL) return "nil";
  if (type == Value_type::NUMBER) {
    std::string string_rep = std::to_string(num);
    string_rep.erase(string_rep.find_last_not_of('0') + 1, std::string::npos);
    string_rep.erase(string_rep.find_last_not_of('.') + 1, std::string::npos);
    return string_rep;
  }
  if (type == Value_type::STRING) return str;
  if (type == Value_type::BOOL) return b00l ? "true" : "false";
  if (type == Value_type::NEEM_CALLABLE) return clb->to_string();
  // Unreachable
  return "undefined";
}
