# Assignment 3


In this assignment, build an interpreter for a programming language. Describe the language incrementally.

## A language for a basic calculator

Consider a language that functions as a calculator.  It supports the following:

- Numerical expression
- Variables
- Printing the result of expressions and strings to the output


Here is a sample program.

```
1 + 2
1 + 2 * 3
let pi = 3.1415
print "PI =" pi:4
let R = 10.0
print "Radius =" R:3
let area = pi * (R^2)
print "Area =" area:0 "and radius =" R:0
```

The output should be:

> ```
> 3.0
> 7.0
> PI = 3.1415
> Radius = 10.000
> Area = 31415 and radius = 10
> ```

**Expressions**

Let's look at the following features:

We can build up numerical expressions such as:

- `1 + 2`
- `1 + 2 * 3`
- `3.1415 * (10 * 10) + 1/2 * 20`

Note:

- Raw expression are printed out in the form of `> ...`.
- Also note the operator precedence.

**Variables**

Variables can be declared:

- `let x = 3.1415 * 10 * 10 + 1/2 * 20`

Variables can be used as part of the expression:

- `x + x / 2.0`

**Printing**

We can use the print statement to display expression and strings.  The results
are displayed in stdout separated by space.

Expressions can be modified by the colon construct (`pi:2`) to specify the
decimal precision the print statement should use.  So `pi:2` becomes `3.14`, and
`pi:3` is `3.142`.

## A language with mutable variables and loops

```
let pi = 3.1415
let r = 0
while (r < 10) {
  print "area =" (pi * r^2):3
  let r = r + 1
}
```

This should output:

> ```
> area = 0.000
> area = 3.142
> area = 12.566
> area = 28.273
> area = 50.264
> area = 78.538
> area = 113.094
> area = 153.934
> area = 201.056
> area = 254.462
> ```

## A language with branching

Suppose we want to find all the pairs of integers $1\leq i\leq 100$ and $1\leq
j\leq 100$ such that:

$$ \frac{2}{3} i - 3.5j = 4.5j $$

Our little programming language can handle it.

```
let i = 0
let count = 0
while (i < 100) {
  let i = i + 1
  let j = 0
  while (j < 100) {
    let j = j + 1
    if 2*i/3 - 3.5*j == 4.5*j {
      print "solution for 2*i/3 - 3.5*j == 4.5*j found:" i:0 j:0
      let count = count + 1
    }
  }
}

print "Total number of solutions:" count:0
```

The expected output should be:


> ```
> solution for 2*i/3 - 3.5*j == 4.5*j found: 12 1 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 24 2 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 36 3 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 48 4 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 60 5 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 72 6 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 84 7 
> solution for 2*i/3 - 3.5*j == 4.5*j found: 96 8 
> Total number of solutions: 8 
> ```