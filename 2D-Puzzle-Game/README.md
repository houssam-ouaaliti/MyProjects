
# 2D Puzzle Game - Inspired by *It Takes Two*

## Overview

This is a school project that implements a 2D puzzle game inspired by *It Takes Two*. The project includes character management, collision systems, graphical interfaces, and puzzle mechanics developed by a team of 8 students.

## Project Documentation

For detailed explanations of the project architecture and implementation, as well as the formal report submitted to the school, please refer to the **`livrables`** folder.

## How to Run

### Compilation

Navigate to the project root directory and compile only the main source code:

```bash
javac -d bin $(find src/back src/front -name "*.java")
```

**Note:** If you don't want to compile the test files, this command excludes `src/test` automatically.

### Execution

Run the game with:

```bash
java -cp bin:src front.Main
```

## Important Notes

- **Window Size:** Make sure to expand the game window to see all game elements properly. The game experience is optimized for a larger display.

## Skills Demonstrated

Object-oriented design in Java · 2D physics and collision detection · GUI development (Swing / AWT) · unit testing · teamwork in a group of 8 · project documentation and user manual (see `livrables/`)
