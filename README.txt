Laboratory Exercise #03
Stack ADT — Infix to Postfix Conversion and Expression Evaluation
Language: C++
Author: Karl Austin Pavia
File: pavia_stack.cpp


-------------------------------
INSTRUCTIONS TO COMPILE AND RUN
-------------------------------

------------------
FOR WINDOWS USERS:
------------------
1. Make sure you have the g++ compiler installed (from MinGW or CodeBlocks).
2. Save this program as: pavia_stack.cpp
3. Open Command Prompt and navigate to the folder where the file is saved.
   Example:
      cd Desktop
4. Compile the program using:
      g++ pavia_stack.cpp -o stack_program.exe
5. Run the program using:
      stack_program.exe
6. When the program runs, type or paste your input following the format:
      (expression)
      (number of variables)
      (variable bindings)
   Then press ENTER after the last line.

Example:
      A+(12*(B-3))
      2
      A=4
      B=9

----------------
FOR LINUX USERS:
----------------
1. Save the file as: pavia_stack.cpp
2. Open Terminal and go to the directory where the file is located.
   Example:
      cd ~/Desktop
3. Compile the program using:
      g++ pavia_stack.cpp -o stack_program
4. Run the program using:
      ./stack_program
5. Type your input in the same format as shown above and press ENTER
   after the last line.

--------------
FOR MAC USERS:
--------------
1. Save the file as: pavia_stack.cpp
2. Open Terminal and navigate to the folder where the file is stored.
   Example:
      cd ~/Documents
3. Compile the program using:
      g++ pavia_stack.cpp -o stack_program
4. Run the program using:
      ./stack_program
5. Type or paste your input in the same format as shown above.

-------------
INPUT FORMAT
-------------
Line 1: Infix expression (e.g., A+(12*(B-3)))
Line 2: Integer k, number of variable bindings
Next k lines: Variable bindings in the form A=4

Example Input:
A+(12*(B-3))
2
A=4
B=9

Expected Output:
A 12 B 3 - * +
76

Error Example Input:
(2+X)*5
0

Output:
2 X + 5 *
ERROR: unknown variable X
















































-