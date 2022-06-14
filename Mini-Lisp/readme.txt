MINI-LISP

Operation

| Name | Symbol | Example |
| ---- | - | ----------- |
| Plus | + | (+ 1 2) => 3 |
| Minus| - | (- 1 2) => -1 |
| Mul | * | (* 2 1) => 2 |
| Div | / | (/ 2 2) => 1 |
| Mod | mod| (mod 10 3) => 1 |
| Grtr | > | (> 1 2) => #f |
| Smlr | < | (< 1 2) => #t |
| Eql | = | (= 1 2) => #f |
| And | and | (and #t #f) => #f |
| Or | or | (or #t #f) => #t |
| Not | not | (not #t) => #f |
| | define |
| | fun |
| | if |

Token Definition

separator= [\t\n\r ]
letter   = [a-z]
digit    = [0-9]
number   = 0|[1-9]digit*|-[1-9]digit*
ID       = letter(letter|digit|'-')*
bool-val = #t|#f

## Grammar and Behavior

1. Program
PROGRAM : STMTS
STMTS   : STMT STMTS | {}
STMT    : EXP | DEF-STMT | PRINT-STMT

2. Print
PRINT_STMT : ( print_num EXP ) | ( print_bool EXP )

3. Expression
EXP   : bool_val | number | VARIABLE | NUM_OP | LOGICAL_OP | FUN_EXP | FUN_CALL | IF_EXP 

4. Numerical Operations 
NUM_OP : PLUS | MINUS | MUL | DIV | MOD | GRTR | SMLR | EQL
