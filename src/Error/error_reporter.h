#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H

#include <string>

class Error_reporter {
public:
  virtual void error(int, std::string) = 0;
  virtual void report(int, std::string, std::string) = 0;
  virtual bool had_error() = 0;
};

#endif // !ERROR_REPORTER_H
