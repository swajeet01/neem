#include <memory>
#include "Ast/expr.h"
#include "Token/token.h"
#include "Token/token_type.h"
#include "Variant/literal.h"
#include "Visitor/ast_printer.h"

int main() {
  auto expr1 = std::make_shared<Binary>(
    std::make_shared<Ast_literal>(
      std::make_shared<Literal>(Literal_type::Number, 10.0)
    ),
    std::make_shared<Token>(std::string {"+"}, 10, Token_type::PLUS,
      std::make_shared<Literal>()),
    std::make_shared<Ast_literal>(
      std::make_shared<Literal>(Literal_type::Number, 20.0)
    )
  );

  auto expr2 = std::make_shared<Binary>(
    std::make_shared<Unary>(
      std::make_shared<Token>(std::string {"-"}, 4, Token_type::MINUS,
        std::make_shared<Literal>()
      ),
      std::make_shared<Ast_literal>(
        std::make_shared<Literal>(Literal_type::Number, 123)
      )
    ),
    std::make_shared<Token>(std::string {"*"}, 4, Token_type::STAR,
      std::make_shared<Literal>()
    ),
    std::make_shared<Grouping>(
      std::make_shared<Ast_literal>(
        std::make_shared<Literal>(Literal_type::Number, 45.67)
      )
    )
  );

  Ast_printer ast_printer;
  ast_printer.print(expr1);
  ast_printer.print(expr2);

  return 0;
}
