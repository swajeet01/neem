<img src="https://github.com/swajeet01/neem/assets/47481301/174eb7c4-a741-42dd-a3a5-70706abbebc1" alt="Neem logo" width="200" >

Hello everyone. This is Swajeet Swarnkar, author of this repo. I wanted to
provide you with an update regarding Neem. Unfortunately, I am very busy
pursuing my postgraduate program, which demands my full attention and
dedication.

As a result I will not be able to finish this project in near future.
However, I want to assure you my deep interest in _Theory of Computation_ and 
_Compiler Design_ remains, unwavering. I have ambitions to finish this project
and do many similar projects in future. Till then :wave:.

[![Build](https://github.com/swajeet01/neem/actions/workflows/cmake.yml/badge.svg)](https://github.com/swajeet01/neem/actions/workflows/cmake.yml)

# Neem Programming Language

A C++ port and extension of
[Lox](https://craftinginterpreters.com/the-lox-language.html)
Language originally created by
[Robert Nystrom](https://twitter.com/intent/user?screen_name=munificentbob)
in his book [Crafting Interpreters](https://craftinginterpreters.com/).

This implementation of Neem is not optimized and sometimes does not follow
best practices. This is because __Neem just serves as a prototype for
another language project currently named _Project L1_.__ Neem might be
refactored and optimized later.

:warning: Neem is not complete yet and is currently under continuous
development.

## Quick tasks

- [ ] Redesign + Refactor to avoid excessive use of `shared_ptr`.
- [ ] Implement a simple block executor for executing blocks without relying
      on finally-like functionality.

## Progress

- [x] Scanning
- [x] Representing code 
- [x] Parsing expressions
- [x] Evaluating expressions
- [x] Statements and state
- [x] Control flow
- [ ] Functions
- [ ] Resolving and binding
- [ ] Structs
- [ ] Arrays/Lists
- [ ] Continue/Break support
- [ ] For-in loop support

## Build and run

The main executable `neem` is not complete yet, but can be built and run.

### Getting the source

Download and extract the source or clone this repository.

```
$ git clone https://github.com/swajeet01/neem.git
$ cd neem/
```

### Generating AST classes

__AST classes are now included in source file, no need to generate__

AST classes can be generated with the `ast_generator.py` script.
`ast_generator.py` reads description of AST classes from a file,
the file should specify AST classes in this format-

- A line starting with `%includes` specifies the files to be included in
generated source files.
- `%includes` must be followed by a '=' followed by list of header file to
include, if a header file is a standard header, its name must be followed
by '\*'.
- Each line not starting with `%` must describe a single AST class.
- Lines describing an AST class must start with a name for that AST class.
- Class name must be followed by a '=' separated by whitespace.
- Following the '=', a class member list separated from '=' by whitespace must
describe the members of the AST class on same line.
- Each class member must be described with its type following by member name
separated by whitespace.
- Each class member in class member list must be separated by ",\<space\>".
- If a member is a `shared_ptr`, its type must be followed be a '\*'.
- File must not contain any trailing newline character ('\n') at the end.

_expr.txt_ and _stmt.txt_ files required for generating AST classes are
included in source (`scripts/expr.txt`, `scripts/stmt.txt`).

Following commands generate AST classes in `src/Ast`.

```
$ mkdir src/Ast/
$ ./scripts/ast_generator.py Expr scripts/expr.txt src/Ast/
$ ./scripts/ast_generator.py Stmt scripts/stmt.txt src/Ast/
```

### Build and run

Build the `neem` executable with CMake.

```
$ mkdir build/
$ cd build/
$ cmake ..
$ cmake --build . -t neem
```

Run and try the `neem` executable, `CTRL+D` to exit.

```
$ ./neem
> let name = "User";
> print "Hello " + name + "!";
Hello User!
> let a = 10.0;
> let b = 20.5;
> print a * b;
205.000000
> print a * b / 5 + 8; 
49.000000
```

In current state, Neem only supports assignment and print statements,
mathematical and logical expressions, scopes, while and for loops.
More language features will be implemented soon.

## Work in Progress!

Source and documentation of Neem is continuously being updated.

