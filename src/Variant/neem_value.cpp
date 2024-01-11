#include <memory>
#include <string>
#include <stdexcept>
#include <variant>

#include "Callable/neem_callable.hpp"
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

Neem_value::Neem_value(Value_type ptype, std::shared_ptr<Neem_callable> callable) {
  if (ptype != Value_type::NEEM_CALLABLE) {
    throw std::runtime_error {"[Internal] Expected Value_type 'NEEM_CALLABLE'."};
  }
  type = ptype;
  data = callable;
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

std::shared_ptr<Neem_callable> Neem_value::get_callable() {
  if (type != Value_type::NEEM_CALLABLE) {
    throw std::runtime_error
      {"[Internal] Tried to retrive member 'callable' while holding other type of value."};
  }
  return std::get<std::shared_ptr<Neem_callable>>(data);
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

void Neem_value::put_callable(std::shared_ptr<Neem_callable> callable) {
  type = Value_type::NEEM_CALLABLE;
  data = callable;
}

std::string Neem_value::to_string() {
  if (type == Value_type::NIL) return "nil";
  if (type == Value_type::NUMBER) {
    std::string string_rep = std::to_string(get_number());
    string_rep.erase(string_rep.find_last_not_of('0') + 1, std::string::npos);
    string_rep.erase(string_rep.find_last_not_of('.') + 1, std::string::npos);
    return string_rep;
  }
  if (type == Value_type::STRING) return get_string();
  if (type == Value_type::BOOL) return get_bool() ? "true" : "false";
  if (type == Value_type::NEEM_CALLABLE) return get_callable()->to_string();
  // Unreachable
  return "undefined";
}
