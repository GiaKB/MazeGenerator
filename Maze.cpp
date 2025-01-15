// Implementation of Maze class
// By Mary Elaine Califf and edited by Gia Berekashvili

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

// Constructor for Maze class
Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

// Equals operator overload method
Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete [] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

// Basic public method that sets numCells equal to rows*columns, unionCounter to 0, and using those, calls the private helper method mazeGeneration using those two
// variables as params.
void Maze::generateMaze()
{
    int numCells = numRows * numColumns;
    int unionCounter = 0;
    mazeGeneration(unionCounter, numCells);
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

// Copy constructor for Maze class
void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}

// This private helper method does the bulk of the work in the public generateMaze() method. Using the logic and details from the assignment doc, we 
// set our cell and neighbor values properly, union if necessary, and knock down necessary walls if needed.
void Maze::mazeGeneration(int unionCounter, int numCells)
{
    DisjointSet mySet(numCells);
    while (unionCounter<numCells-1)
    {
        int cell = rand() % numCells;
        int direction = rand() % 4;
        int neighbor;
        
        switch (direction)
        {
            case 0:
            {
                if (cell%numColumns != 0)
                {
                    neighbor = cell - 1;
                }
                else
                {
                    neighbor = cell + 1;
                    direction = 2;
                }
                break;
            }
            case 1:
            {
                if (cell / numColumns < numRows - 1)
                {
                    neighbor = cell + numColumns;
                }
                else
                {
                    neighbor = cell - numColumns;
                    direction = 3;
                }
                break;
            }
            case 2:
            {
                if (cell % numColumns != numColumns - 1)
                {
                    neighbor = cell + 1;
                }
                else
                {

                    neighbor = cell - 1;
                    direction = 0;
                }
                break;
            }
            case 3:
            {
                if (cell / numColumns > 0)
                {
                    neighbor = cell - numColumns;
                }
                else
                {
                    neighbor = cell + numColumns;
                    direction = 1;
                }
                break;
            }
        }
        if (mySet.find(cell) != mySet.find(neighbor))
        {
            mySet.doUnion(cell, neighbor);
            unionCounter++;

            if (direction == 0)
            {
                mazeWalls[neighbor].east = false;
            }

            else if (direction == 1)
            {
                mazeWalls[cell].south = false;
            }

            else if (direction == 2)
            {
                mazeWalls[cell].east = false;
            }

            else if (direction == 3)
            {
                mazeWalls[neighbor].south = false;
            }
        }  
    }
}
