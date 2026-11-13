# Specification notes
Summarises [CCoursework.pdf](CCoursework.pdf)
- [The program to write](#the-program-to-write)
- [Constraints](#constraints)
- [Maze rules](#maze-rules)
- [Getting a good mark](#getting-a-good-mark)
- [What to submit](#what-to-submit)

## The program to write 
Completing the basic stages will get a pass mark if you write reasonable code. 
<br><br>
Basic Stage 1: Display a maze in the drawing window.
<br><br>
Basic Stage 2: Display a robot and animate it so that it moves through the maze to the exit 
marker.
<br><br>
Stage 3: Implement a basic maze search algorithm to move the robot from the entrance to the 
exit marker.
<br><br>
Stage 4: Implement an algorithm to generate mazes, with a single entrance and single exit.
<br><br>
Stage 5: Improve your robot search algorithm to work with any maze you can generate. 

## Constraints 
- You cannot use any other third-party libraries or add-ons. 
- Do not use any platform-specific header files or libraries (e.g., windows.h). 
- Do not modify the graphics.h or graphics.c files.

## Maze rules
All mazes should follow these rules:
- Squares are identified by (x, y) coordinates, where x is the column counting from the 
left and y is the row counting from the top, so (0, 0) is the top-left square.
- __The maze is surrounded by an outer wall one square thick__, except for exactly one 
entrance and one exit, each a single-square gap in the outer wall.
- There must be at least one path of empty squares from the entrance to the exit.
- Any square outside the grid is treated as a wall, so canMoveForward returns false and 
the robot can never leave the maze.
- The maze can be any size, provided the whole maze fits in the drawing window. The 
drawing window can be resized to make it bigger.

## Getting a good mark: <br>
Marking will take into account the quality of the code you write. In 
particular pay attention to the following: 
 
- Proper declaration, definition and use of functions, variables and data structures. 
- The layout and presentation of the source code. 
- Appropriate selection of variable and function names. 
- Appropriate use of comments. Comments should add information to the source code, 
not duplicate what the code already says (e.g., no comments like "This is a variable"!).                                                             
- As much as possible your code should be fully readable without having to add 
comments. 
- Selection of a suitable design to provide an effective solution to the problem in 
question.

## What to Submit 
Submitted on Moodle, via the upload link for the C Coursework as a __.zip__ file only. <br>
__The zipfile must be named COMP0002CW1.zip.__ 
 
The zipfile should contain: 
- The C source code file(s). 
- A README file (see below). 
- Any data files or image files needed to run the program. 

__DO NOT__ submit the drawing app files (drawapp-5.0.jar, graphics.h, graphics.c). 
 
The README should include the following: 
- A concise description of what the program does. You might use one or two (small) screenshots to help explain your program. 
- The command(s) needed to compile and run the program. 
This should be 1 page at most and use plain text or markdown format. 

Anonymous marking of coursework is used, so don’t include your name or student number in the files submitted.