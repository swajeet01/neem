#include <memory>
#include "Ast/expr.h"
#include "Visitor/ast_printer.h"

int main() {
  auto expr = std::make_shared<Binary>(
    std::make_shared<Ast_literal>(
      std::make_shared<Literal>(Literal_type::Number, 10.0)
    ),
    std::make_shared<Token>(std::string {"+"}, 10, Token_type::PLUS,
      std::make_shared<Literal>()),
    std::make_shared<Ast_literal>(
      std::make_shared<Literal>(Literal_type::Number, 20.0)
    )
  );
  Ast_printer ast_printer;
  ast_printer.print(expr);
  return 0;
}
