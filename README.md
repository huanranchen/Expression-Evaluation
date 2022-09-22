# Expression-Evaluation
Expression Evaluation in c++
Background:

We have introduced the algorithm for expression evaluation in class. Now we want to extend the algorithm by requiring operators that can be handled including +, -, *, /, % (modular), ^ (power), (, ).

Requirement:
The operator-first algorithm is used, and only integers are retained for the intermediate results of the calculation.

Input:
The first row is an integer N. This means that there are N expressions below.

The following N lines from the second line onwards are N expressions consisting of integers.

Output:
There are N lines, and each line is the result of the calculation of the corresponding expression.

If there is an error in the expression, the output is: error.

If there is a division of 0 during the calculation, the output is: Divide 0.

Note:

In the expression, pay special attention if the operand appears negative (e.g. -8). For example.

10 plus -8 is expressed as: 10 + -8.

10 minus -8 is expressed as: 10 - -8.
