# LatinSquareGame
Latin Square Game Implementation

## Overview

The Latin Square Game is a C-based console application that allows users to interactively fill in a Latin square grid while adhering to the rules of the game. Each number must appear exactly once in each row and column. The program enables users to input values, clear cells, save progress, and check for winning conditions.

## Features

- **Interactive Gameplay**: Users can enter values in the grid, clear cells, and receive real-time feedback.
- **File Operations**: The program can read a Latin square from an input file and save the current state to an output file.
- **Validation**: Ensures that the user input adheres to the rules of the Latin square, preventing invalid moves.
- **Winning Conditions**: Automatically checks if the game has been won after each move.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- A terminal or command prompt

### Installation

1. Clone this repository or download the source code files.
2. Navigate to the project directory in your terminal.
3. Compile the program using the following command:

   ```bash
   gcc -o latin_square latin_square.c

4. Run the program using: => (inputfile is your inputfile name!!)
 ```bash
 ./latinsquare inputfile.txt    
