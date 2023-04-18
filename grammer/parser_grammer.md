# Parser grammer

## Subset of grammer

```
expression  ->  literal | unary | binary | grouping ;
literal     ->  NUMBER | STRING | "true" | "false" | "nil" ;
unary       ->  ( "-" | "!" ) expression ;
binary      ->  expression operator expression ;
grouping    ->  "(" expression ")" ;
operator    ->  "==" | "!=" | "<=" | "<" | ">=" | ">" |
                "+" | "-" | "/" | "*" ;
```
