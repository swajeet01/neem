#ifndef COMMON_H
#define COMMON_H

namespace common {
  constexpr char newl       {'\n'};
  constexpr int EX_DATAERR  {65};
  constexpr int EX_SOFTWARE {70};
  constexpr int EX_IOERR    {74};

  constexpr auto notice =
R"(Neem Programming Language,  Copyright (C) 2023  Swajeet Swarnkar.
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it under
certain conditions. See <https://www.gnu.org/licenses/>.)";

};

#endif // !COMMON_H
