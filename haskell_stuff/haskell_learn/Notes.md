# A little bit of history
- Alonzo Church, with the intention of investigating the foundations of mathematics, invented lambda calculus in the 1930s.
- John McCarthy (created Lisp at 1958) realized the connection between programming and lambda calculus.
- In the early 1970s, Robin Milner created a more rigorous functional programming language named ML (it was intended to help with automated proofs of theorems, but it gained more general computing tasks).
- After three years of work, Haskell 1.0 specification was published in 1990.
- Since its publication in 1990, the Haskell language standard has seen five revisions.
- Haskell for a long time remained as an academic language ("avoid success at all costs"), but with time it escaped from academia and gained attention of the general public.
# Environment and some arithmetic
- GHC (Glasgow Haskell Compiler) components:
    - ghc: Optimizing compiler that generates fast native code
    - ghci: Interactive interpreter and debugger
    - runghc: Program for run Haskell programs as scripts, without needing to compile them.
- Need to specify negative values inside parentheses to remove ambiguity and some parser errors. For example, in Haskell 2 \*-3 will throw an error because it will interpret \*- as a single operator, so, to fix, put 2 \*(-3).   
- Not equal operator is "/="
- Not operator is the word "not"
- The math constant pi ($\pi$) is defined, but $e$ is undefined.
- Defining $e$ in Haskell (temporary definition): let e = exp 1 | Haskell does not require parentheses around function arguments
- The (^) operator can only raise a number to an integer power. For floating point number as exponent use (\*\*) operator.
- Lists are surrounded by square brackets, with elements separated by commas.
- All elements in a list must be the same type.
- Lists can be written using the enumeration notation, for example: [1..10]
- Lists can be concatenate with the (++) operator
- An element can be append to a list with the (:) operator | The first operator must be the element to be appended
- putStrLn function prints a string
- In Haskell a string is a list of characters, so the list operators can be used
- Rational numbers in Haskell are constructed by (%) operator, with the numerator on the left and denominator on the right
# Why care about types
- Every expression and function in Haskell has a type
- Types are an abstraction layer that adds meaning for bytes
- Types in Haskell are strong, static and *can* be automatically inferred
- Casting must be explicit
# Some basic types
- Char
- Bool
- Int
- Integer
- Double
- To explicitly specify the type: var :: Type | :: + type is called *type signature*
- Tuples: Fixed-size collection of values, where each value can have a different type
- In Haskell, function application is left associative
- Pure functions don't have side effects, while impure functions do
- Impure functions results will begin with IO
- Haskell does not have a return keyword
- In Haskell, variables don't change (they are a name for a particular expression)
- Indentation is important
--- 
# References:
1. [What's the difference between the classes Floating and Fractional in Haskell?](https://stackoverflow.com/questions/41964228/whats-the-difference-between-the-classes-floating-and-fractional-in-haskell)
2. [How to throw an exception and exit the program in Haskell?](https://stackoverflow.com/questions/6070316/how-to-throw-an-exception-and-exit-the-program-in-haskell)
3. [how to have multiple if statements in Haskell?](https://stackoverflow.com/questions/74399187/how-to-have-multiple-if-statements-in-haskell)
