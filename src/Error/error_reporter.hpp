#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H

#include <string>

class Error_reporter {
public:
  virtual void report(size_t, std::string, std::string) = 0;
  virtual bool had_error() = 0;
  virtual ~Error_reporter() = default;
};

#endif // !ERROR_REPORTER_H
