# Everything You Need to Know About Compilers
# Compiler vs Interpreter

- **Compiler**: Converts a high-level programming language into a lower-level language to create an executable program.
- **Interpreter**: Directly executes instructions written in a programming or scripting language without requiring compilation.

## Examples

- **Compilers**: GCC, Clang, MSVC
- **Interpreters**: Python interpreter, JavaScript engines (like V8)

---

# Compiler Modules

A typical compiler consists of the following modules:

- **Lexer**: Breaks down source code into tokens.
- **Parser**: Takes tokens and creates a parse tree or abstract syntax tree (AST).
- **Semantic Analyzer**: Checks for semantic errors and ensures code adheres to language rules.
- **Optimizer**: Improves performance of the code without changing its behavior.
- **Code Generator**: Translates the optimized intermediate representation into target machine code.


>Semantic Analysis,Optimization and code generator are collectively known as the "middle end" of the compiler or "generator".
---

# Compilation Steps

The compilation process involves several stages:

1. **Preprocessing**: Handles directives like `#include` and `#define` in C/C++.
2. **Compilation**: Translates preprocessed code into assembly language  -o code( g++ test.cpp -o test).
3. **Assembly**: Converts assembly language into machine code (object files).
4. **Linking**: Combines object files and libraries into a final executable program.

---

# Runtime Environment

The runtime environment provides services and resources needed for program execution:

- The OS loads the program into RAM and allocates resources.
- The program counter points to the first instruction, which jumps to `main()`.
- Instructions are run line by line.
- Manages memory allocation and deallocation for heap and stack.
- Execution ends when `return 0;` is reached.

---

## Summary Diagram

```
your code (main.cpp)
    ↓
[Preprocessor]
    ↓
[Compiler]
    ↓
[Assembler]
    ↓
[Linker]
    ↓
Executable
    ↓
[Runtime Environment]
    ↓
Output
```

---

# Compiler Optimization

Compiler optimization is the process of improving the performance and efficiency of the generated code without changing its output. Optimizations can make programs run faster, use less memory, or reduce executable size.

## Types of Compiler Optimization (from CS50)

- **Peephole Optimization**: Makes small, local changes to a short sequence of instructions, such as removing redundant code or simplifying expressions.
- **Loop Optimization**: Improves the performance of loops, e.g., by unrolling loops, moving invariant code outside the loop, or reducing loop overhead.
- **Inlining**: Replaces a function call with the actual code of the function, reducing function call overhead.
- **Dead Code Elimination**: Removes code that will never be executed or whose results are never used.
- **Constant Folding**: Computes constant expressions at compile time rather than at runtime.
- **Strength Reduction**: Replaces expensive operations (like multiplication) with cheaper ones (like addition or bit shifting).
- **Common Subexpression Elimination**: Identifies and reuses repeated expressions to avoid redundant calculations.

> These optimizations help compilers generate more efficient executables, improving speed and resource usage.

# Everything You Need to Know About Compilers

[Badges: language, license, status]

## Table of Contents  
1. Introduction  
2. Compiler vs Interpreter  
3. Compiler Architecture  
   - Diagram / Flow  
   - Modules (lexer, parser, semantic, optimizer, code generator)  
4. Compilation Phases  
   - Preprocessing, parsing, semantic, IR, optimization, codegen, linking  
5. Semantic Analysis & Symbol Table  
6. Intermediate Representation (IR)  
7. Optimizations  
   - Peephole, constant folding, dead code elimination, etc.  
   - Examples before/after  
8. Code Generation & Backend  
   - Target architecture  
   - Register allocation, function calls  
9. Error Handling  
10. AST / Parse Tree Output  
11. Usage & Demo  
    ```bash
    build step…
    run step…
    ```  
    - Sample inputs and outputs  
12. Performance / Benchmarks  
13. Roadmap / Future Work  
14. Contributing  
15. License  
