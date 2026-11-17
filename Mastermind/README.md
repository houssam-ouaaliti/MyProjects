# ♟️ Mastermind Project: Strategy Implementation

This project is a **school assignment** developed by a two-person team (binome). It involves the implementation of the Mastermind board game, focusing on developing and analyzing various game-solving strategies for the "codebreaker" and "codemaker" roles, as well as providing a graphical user interface (GUI).

* **Authors:** Ghadi ABDALLAH, Houssam OUAALITI
* **Context:** SCHOOL Project (Info CPP )
* **Year:** 2023/2024
* **Default Configuration:** 4 pegs and 8 colors.

***

## 🚀 Implemented Strategies and Performance Analysis

The project explores a range of Codebreaker strategies, from pure randomness to information-based algorithms.

### 1. Codebreaker Strategies

**Codebreaker 0 Strategy**
The codebreaker generates a random guess at each turn. Each guess is completely independent, purely relying on randomness.

**Codebreaker 1 Strategy**
The codebreaker maintains a list of all possible combinations and randomly selects a guess from this list. After each guess, the chosen combination is removed from the pool to avoid repeating guesses.

**Codebreaker 2 Strategy**
The codebreaker starts with a random guess. From the second turn onward, it maintains a set of all possible solutions consistent with previous feedback. At each turn, it randomly selects a guess from this set and updates the possibilities based on the feedback, ensuring guesses progressively narrow down the solution space.


**Codebreaker 3 Strategy**
This codebreaker implements a minimax-like approach: it keeps track of all possible codes and all possible feedbacks. At each turn, it chooses the guess that minimizes the maximum number of remaining possibilities after considering all potential feedbacks. This strategy actively uses previous feedback to narrow the solution space optimally, aiming to solve the code in the fewest moves possible.

**Human Codebreaker Strategy**
The codebreaker is controlled by a human player. The player inputs their guess manually at each turn. Input is validated to ensure the correct length and valid colors. The game loop handles feedback, so the human only focuses on making guesses.

### 2. Codemaker Strategies

**Codemaker 0 Strategy**
The codemaker selects a secret code at the start of the game. When evaluating a guess, it only counts how many colors are correctly placed (white pegs) and ignores correct colors in the wrong positions (black pegs). This is a partial evaluation, providing limited feedback to the codebreaker.

**Codemaker 1 Strategy**
The codemaker generates a secret code randomly at the start. It uses the full evaluation function, returning both the number of correctly placed colors (white pegs) and the number of correct colors in wrong positions (black pegs), providing complete feedback to the codebreaker.
***

**Codemaker 2 Strategy**
The codemaker adapts dynamically: it maintains a set of all possible codes and, after each guess, chooses a secret code that maximizes the number of remaining possible solutions. This makes the codebreaker’s task harder because the “target” adapts while staying consistent with prior feedback — in a sense, it can “cheat” within the rules.


## ⚙️ Project Structure and Organization

The code is logically structured into Python packages and modules for modularity and clarity.

***

## ⚠️ Execution Instructions (Compatibility Notice)
**For proper execution, all Python files should be in the same directory.**
### Deployment for Execution (Recommended Method)

1.  **Flattening:** Move **ALL Python files (`.py`)** from all subdirectories (`codebreakers/`, `codemakers/`, `tests/`, etc.) directly into the **root directory** of the project.
2.  **Execution:** Run the scripts from the root directory.

### Launch Examples

Ensure you have the necessary dependencies installed (`numpy`, `matplotlib`, `tkinter`).

* **To Launch the Graphical Interface (Human vs. CM1):**
    ```bash
    python3 mastermind_gui.py
    ```

**Project Report:** The file `Rapport Projet Mastermind.pdf` contains the official project report requested by the school. It includes a detailed analysis of the results, strategy performance.

## Skills Demonstrated

Algorithm design and strategy comparison · constraint-based search-space reduction · statistical performance analysis (NumPy, Matplotlib) · GUI development (Tkinter) · unit testing · pair programming and technical reporting
