#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum class Token_type {
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACK, RIGHT_BRACK,
  COMMA, DOT, MINUS, PLUS, SLASH, STAR, SEMI_COL, MOD,

  BANG, BANG_EQ,
  EQ, EQ_EQ,
  GREATER, GREATER_EQ,
  LESSER, LESSER_EQ,

  IDENTIFIER, STRING, NUMBER,

  LET, NTRUE, NFALSE, AND, OR, IF, ELSE, FN, WHILE, FOR, IN, STRUCT, THIS,
  BREAK, CONTINUE, RETURN, NIL, PRINT,

  NEOF
};

#endif // !TOKEN_TYPE_H
