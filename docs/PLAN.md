# Plan
Course checklist:
- [x] Display a maze
- [x] Display a robot
- [x] Implement a maze search algorithm
- [x] Implement a maze generator algorithm
- [x] Improve searcher algorithm to work with all possible mazes

Main parts:
- [x] [2D maze](#2d-maze)
- [x] [3D maze](#3d-maze)
- [x] [Maze Searcher](#maze-searcher)
- [x] [Maze Generator](#maze-generator)

## 2D maze
TO-DO:
- [x] Grid
- [x] Walls
- [x] Robot

### Robot Interface
As according to the [CCoursework specification](CCoursework.pdf)

>The robot is simple and only these functions should be provided to control the robot:<br>
>• forward() – move forward to the next square in the direction the robot is facing. If there is a maze wall in front of the robot it does not move.<br>
>• left() – turn the robot direction left (anti-clockwise) by 90 degrees, while remaining in the same position.<br>
>• right() – turn the robot direction right (clockwise) by 90 degrees, while remaining in the same position.<br>
>• int atMarker() – return true if the robot is on the exit marker, otherwise false.<br>
>• int canMoveForward() – return true if the robot can move forward as there is no maze wall in front of it. Return false otherwise.<br>

## 3D maze
TO-DO:
- [x] Draw floor and sky
- [x] Determine visible walls
- [x] Draw visible walls
- [x] Lighting

### Column based ray-casting approach
Cast a ray from the player's position.
Find the first wall the ray intersects.
Calculate the distance to that wall.
Calculate how tall that wall should appear.
Draw a vertical strip of pixels.

## Maze Searcher
TO_DO:
- [x] Implement simple placeholder algorithm
- [x] Choose Algorithm
- [x] Implement connectivity using [Robot Interface](#robot-interface)


## Maze Generator
TO-DO:
- [x] Choose algorithm
- [x] Implement algorithm