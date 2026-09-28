Expression Tree Evaluation
This project implements an Expression Tree using the given postfix expression:

`8 3 2 * + 6 2 / -`

Contents

- `expression_tree.c` — builds the binary Expression Tree from the postfix expression and provides inorder, preorder, and postorder traversals.
- `input.txt` — contains the given postfix expression used for the program.
- `output.txt` — contains the final program output, including the tree traversals and evaluation results.
- `trace_output.txt` — contains the important intermediate steps of postfix stack evaluation and Expression Tree evaluation.
- `trace_table.pdf` — detailed trace table showing the operations performed during evaluation.
- `complexity_analysis.pdf` — time and space complexity analysis of both evaluation approaches.
- `comparison_table.pdf` — comparison of stack-based postfix evaluation and Expression Tree evaluation.

 Project Objectives

1. Construct an Expression Tree from the given postfix expression.
2. Display the Expression Tree structure.
3. Perform inorder, preorder, and postorder traversals.
4. Evaluate the postfix expression using a stack.
5. Evaluate the same expression using the Expression Tree.
6. Record important intermediate operations using trace tables.
7. Compare both approaches based on operations, data structure, time complexity, and space requirements.
8. Analyse how the Expression Tree provides additional structural information compared with direct postfix evaluation.

 Given Postfix Expression

`8 3 2 * + 6 2 / -`

 Equivalent Infix Expression

`(8 + (3 * 2)) - (6 / 2)`

 Evaluation

The expression is evaluated as:

`8 + (3 × 2) - (6 ÷ 2)`

`= 8 + 6 - 3`

`= 11`

Both evaluation methods produce the same final result:

**Result = 11**

Expression Tree

The Expression Tree represents the operands and operators in a hierarchical structure. 
The operators are stored as internal nodes and the operands are stored as leaf nodes.

 Tree Traversals

The program displays:

- Inorder traversal
- Preorder traversal
- Postorder traversal

The postorder traversal corresponds to the original postfix expression.

 Evaluation Methods

1. Stack-Based Postfix Evaluation

The postfix expression is processed from left to right. Operands are pushed onto a stack, and whenever an operator is encountered, the required operands are popped, the operation is performed, and the result is pushed back onto the stack.

 2. Expression Tree Evaluation

The Expression Tree is evaluated recursively. The left and right subtrees are evaluated first, and then the operator at the current node is applied to their results.

 Comparison

The two approaches are compared based on:

- Number of operations
- Data structure used
- Time complexity
- Space requirements
- Structural information provided

The postfix method directly evaluates the expression using a stack, while the Expression Tree represents the complete hierarchical structure of the expression.

 Conclusion

This project demonstrates the use of stacks and binary trees for expression evaluation. Both methods produce the same result, `11`. The stack-based approach directly evaluates the postfix expression, whereas the Expression Tree provides additional structural information about the relationship between operands and operators.

 How to Run

Compile the C program using a C compiler:

```bash
gcc expression_tree.c -o expression_tree
