# Parser grammer

## Subset of grammer

```
expression  ->  literal | unary | binary | grouping ;
literal     ->  NUMBER | STRING | "true" | "false" | "nil" ;
unary       ->  ( "-" | "!" ) expression ;
binary      ->  expression operator expression ;
grouping    ->  "(" expression ")" ;
operator    ->  "==" | "!=" | "<=" | "<" | ">=" | ">" |
                "+" | "-" | "/" | "*" | "%" ;
```

## Subset of grammer with amibiguity removed

```
expression  ->  equality ;
equality    ->  comparison ( ( "!=" | "==" ) comparison )* ;
comparison  ->  term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term        ->  factor ( ( "-" | "+" ) factor )* ;
factor      ->  unary ( ( "/" | "*" | "%" ) unary )* ;
unary       ->  ( "!" | "-" ) unary | primary ;
primary     ->  NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
```
