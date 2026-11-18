# maze_solver
C coursework for UCL's *COMP0002: Principles of Programming* course.<br>
Course work specification can be found at [CCoursework.pdf](docs/CCoursework.pdf), with notes thereof [here](docs/SPECIFICATION-NOTES.md).

# Maze Solver

This project implements a simple maze-solving program in C for the COMP0002 coursework. It displays a maze, renders a robot moving through it, and demonstrates both a maze generator and a search strategy that guides the robot to the exit.

## What the program does

- Draws a maze in a window using the provided graphics library.
- Renders the maze in __both 2D and 3D__ views.
- Displays a robot and animates its movement through the maze.
- Generates mazes with a single entrance and exit while keeping the outer wall intact.
- Solves the maze by using a robot interface with movement and collision checks.

## Build and run

Install GNU Make, GCC (such as MinGW-w64 on Windows), and Java, then run these commands from the project root. On Windows, use `make` if available or replace it with `mingw32-make`:

```bash
make
make run
```

This compiles the program and launches it using the included drawing application. The Makefile supports macOS, Linux, Windows Command Prompt/PowerShell, and Git Bash.

Choose a texture theme with a Make variable (the same syntax works in all shells):

```bash
make run TEXTURE_SET=default
make run TEXTURE_SET=minecraft
make run TEXTURE_SET=wolfenstein
make run TEXTURE_SET=backrooms
```

Set the maze size when building and running (defaults to 10; valid sizes are 3–100):

```bash
make run MAZE_SIZE=15
```

Invalid maze sizes are rejected by the compiler. To remove the generated executable:

```bash
make clean
```

## Project structure

- `source/` — C source files for the maze logic, rendering, and robot behaviour
- `include/` — headers used across the project
- `graphics/` — drawing utilities and window support
- `textures/` — texture sets used for the 3D view
- `docs/` — coursework notes and specification documents