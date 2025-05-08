# Bisakol
A toy programming language with keywords resembling that of the Cebuano language from the Philippines.  

##### TODO
- Lexer (in progress)
- Parser
- Semantic Analysis
- Intermediate Representation (AST)
- Code Generator (to C)

# Basic syntax
```
// A function that returns an ent (32-bit interger for 64-bit systems)
fn main() -> ent {
    // Assignment syntax. Type is inferred
    tugoti x = 5;
    tugoti y = 7;

    // For loop that binds a variable from 0 to 5
    por z sa 0..5 {
        x -= z;
    }

    // If statement
    kung x + y == 12 {
        balik 0;    // Return 0
    } kung kani x - y <= 0 {    // Else if
        balik 1;
    } kung wala {               // Else
        balik 2;
    }
}
```

# Library used
[c-vector](https://github.com/wrkean/c-vector) (my own implementation of C++ vectors in C)
