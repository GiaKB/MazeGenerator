This README file helps the reader the understand the goal of this project and how to utilize it.

This project utilizes disjoint sets to create an nXn maze using |'s and -'s for vertical and horizontal walls, respectively.

To run the program, the files DisjointSet.cpp, Maze.cpp, and MazeGenerator.cpp must be compiled together. After compilation, you can run the program by typing this into the console:
outfileName numRows numColumns fileForMazeToBeSavedTo Seed (0 if unspecified).

The function of disjoint sets in this program is to "knock down walls" and join two cells. Once all of these cells are joined, the maze is completed.

After running this, your custom, randomized maze will be printed into that .txt file. Note that this code does not work with a non-square maze dimension (i.e.; 5x4 or 4x9).
