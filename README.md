# Sudoku Solver using Breadth First Search and Best First Search
# Overview
This is a C++ program that solves Sudoku puzzles using either Breadth First Search (BFS) or Best First Search (BFS). Given an input Sudoku grid containing the initial state of the puzzle, the program applies a series of constraints and heuristics to find a solution, outputting the final state of the puzzle.

# Requirements
C++ compiler 

# How it works
The program represents the Sudoku puzzle as a 2D array of SudokuSquareSets(a set of possible values that could be in that position). It then applies a series of constraints and heuristics to find the solution. For BFS, the program uses a queue to keep track of the next state to explore. For BFS, the program uses a priority queue that hueristics to prioritize the next state to explore.

The program continues to explore states until a solution is found or all possible states have been explored. If a solution is found, the program outputs the final state of the puzzle.



Acknowledgements
This project was inspired by the Sudoku puzzle, a popular game that tests logic and reasoning skills.
Thanks to the creators of C++ and the various libraries used in this project.