# Calvodax

Calvodax is a calculator, that can represent numbers with unlimited precision.

## Functionality
* Calvodax can read expressions from stdin and evaluate them.
* It can store variables and use them later.
* Basic operations - addition, subtraction, multiplication.
* For integers also division and remainder.
* Functions for rounding, factorial and exponentiation.
* The current state of saved variables can be stored in a human readable file.
* Numbers are stored as two types. Scientific notation (10^n) or normal notation.

### Expresions
* Expresions are expresed in standard notation. For a more complex grammar
  see [Grammar](./grammar)

#### Example
```
foo = 1 + 3
bar = factorial ( foo )
science = 10e189

science % bar
```

## Polymorphism
Where does Calvodax use polymorphism:
* Nodes of the abstract syntax tree, while evaluating expressions.
* Number representation different types of number are descendents of an abstract
  Number class.

```marmaid
classDiagram
    Number <|-- Integer
    Number <|-- Rational
    Integer <|-- Dense
    Integer <|-- Sparse
    class Number{

    }
    class Rational{
        Integer numerator
        Integer denominator
    }
```