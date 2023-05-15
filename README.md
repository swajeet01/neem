# Neem Programming Language

A C++ port and extension of
[Lox](https://craftinginterpreters.com/the-lox-language.html)
Language originally created by
[Robert Nystrom](https://twitter.com/intent/user?screen_name=munificentbob)
in his book [Crafting Interpreters](https://craftinginterpreters.com/).

This implementation of Neem is not optimized and sometimes does not follow
best practices, it uses C++11 features and avoids any features introduced in
later C++ standards. This is because __Neem just serves as a prototype for
another language project currently named _Project L1_.__

:warning: Neem is not complete yet and is currently under continuous
development.

## Progress

- [x] Scanning
- [x] Representing code 
- [x] Parsing expressions
- [ ] Evaluating expressions
- [ ] Statements and state
- [ ] Control flow
- [ ] Functions
- [ ] Resolving and binding
- [ ] Structs

## Build and run

The main executable `neem` is not complete yet, but can be built and run.

### Getting the source

Download and extract the source or clone this repository.
```bash
$ git clone https://github.com/swajeet01/neem.git
$ cd neem/
```

### Generating AST classes

AST classes must be generated with the `ast_generator.py` script.
`ast_generator.py` reads description of AST classes from a file,
the file should specify AST classes in this format-

- Each line must describe a single AST class.
- Each line must start with a name for an AST class.
- Class name must be followed by a ':'.
- Following the ':', class members must be of an AST class described on same
line separated by ",\<space\>".
- File must not contain any trailing newline character ('\n') at end.

Current implementation only supports expressions, AST classes for expressions
can be generated by following `expr.txt` file.

```
Binary          :   Expr left, Token op, Expr right
Grouping        :   Expr expr
Unary           :   Token op, Expr right
Ast_literal     :   Literal value
```
Save above contents to file name `expr.txt` or any suitable name, and run
following commands to generate AST classes in `src/Ast`.

```bash
$ mkdir src/Ast/
$ ./scripts/ast_generator.py Expr <path to your expr.txt> src/Ast/
```

### Build and run

Build the `neem` executable with CMake.

```bash
$ mkdir build/
$ cd build/
$ cmake ..
$ make neem
```

Run and test the `neem` executable, `CTRL+D` to exit.

```bash
$ ./neem
> 1 + 2
(+ 1.000000 2.000000)
> 1 + 2 == 3
(== (+ 1.000000 2.000000) 3.000000)
> (5 * 1) - 7 != false
(!= (- (group (* 5.000000 1.000000)) 7.000000) false)
> Bye!
```

In current state, Neem only prints the AST in a readable format.
Evaluation and more language features will be implemented soon.

## Work in Progress!

Source and documentation of Neem is continuously being updated.
