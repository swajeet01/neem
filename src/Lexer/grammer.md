# Grammer for lexical analyzer

```
ws          ->      [ \n\t\r]
letter_     ->      [a-zA-Z]
digit       ->      [0-9]

identifier  ->      letter_(letter_|digit)*
string      ->      "(letter|digit|ws)*"
number      ->      digit+(\.digit+)?
```
