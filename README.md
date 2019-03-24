# PDA-to-CFG

This code implements the algorithm in Introduction to the Theory of Computation by Michael Sipser.

## Dependencies
  - Branch master:
    * Flex >= 2.5.32  
    * Bison >= 2.3
  
## Installation

After cloning the project, just run the make command.

## PDA Encoding

The main program takes input from the stardard input (stdin). You can write a file using the following grammar
to redirect to the stdin. 

- PDA := STATES '|' ALPHABET '|' STACK_ALPHABET '|' FINAL_STATES '|' TRANSITIONS
- STATES :=  ID | ID ',' STATES
- ALPHABET :=  ID | ID ',' ALPHABET
- STACK_ALPHABET :=  ID | ID ',' STACK_ALPHABET
- FINAL_STATES :=  ID | ID ',' FINAL_STATES
- TRANSITIONS := TRANSITION | TRANSITION TRANSITIONS
- TRANSITION := ID ',' ID ',' ID '->' ID ',' ID ';'

ID's are identifiers, which are alphanumeric sequence of characters (including the symbols '_' and '$'). The enconding
for the TRANSITION rule is:

- The first ID refers to a state
- The second ID refers to current input symbol
- The third ID refers to the symbol at the top of the stack
- The forth ID refers to the next state
- The fifth ID refers to the next symbol at the top of the stack

If you want to include an epsilon transition in your PDA you should
just the string 'epsilon'.

## Examples of PDA Encodings

- q1, q2, q3, q4 |
0, 1 |
$, 0 |
q1, q4 |
q1, epsilon, epsilon -> q2, $;
q2, 0, epsilon -> q2, 0;
q2, 1, 0 -> q3, epsilon;
q3, 1, 0 -> q3, epsilon;
q3, epsilon, $ -> q4, epsilon;

- q_1, q_2, q_3, q_4, q_5, q_6, q_7 |
a, b, c |
$, a |
q_4, q_7 |
q_1, epsilon, epsilon -> q_2, $;
q_2, epsilon, epsilon -> q_3, epsilon;
q_3, b, a -> q_3, epsilon;
q_3, epsilon, $ -> q_4, epsilon;
q_4, c, epsilon -> q_4, epsilon;
q_2, a, epsilon -> q_2, a;
q_2, epsilon, epsilon -> q_5, epsilon;
q_5, b, epsilon -> q_5, epsilon;
q_5, epsilon, epsilon -> q_6, epsilon;
q_6, c, a -> q_6, epsilon;
q_6, epsilon, $ -> q_7, epsilon;

## Running Examples
- pdatocfg < pdas/pda1.txt
- pdatocfg < pdas/pda2.txt

## References
Sipser, M. Introduction to the Theory of Computation. 3rd edition. CENGAGE.
