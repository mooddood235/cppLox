# cppLox

C++ implementation of the Lox language described in the book [Crafting Interpreters](https://craftinginterpreters.com/) by Robert Nystrom. 

## Features
- Dynamic Typing
- Lexical Scoping
- Variables
- First-Class Functions
- Control Flow
  - Conditionals
  - For Loops
  - While Loops

## Implementation
- Recursive Descent Parser
- Tree Walk Interpreter

## Code Snippet
```
fun fib(n){
    if (n <= 1) {return n;}
    return fib(n - 1) + fib(n - 2);
}
var time0 = clock();
for (var i = 0; i < 20; i = i + 1){
    print "Fib(i): " + fib(i);
}
print "Time Elapsed: " + (clock() - time0);
```

## Book Cover
![header](https://github.com/user-attachments/assets/019952aa-00ba-4c20-9b19-d6ad6cc9eff0)
