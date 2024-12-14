// ============================================================================
// File: ExhaustiveSearch.cpp
// ============================================================================
// Programmer: Thomas Ortiz, Alexander Sanchez, Ansh Tomar, Edgar Cardenas
// Date: December 2024
// Class: CPSC 335 Algorithm Engineering
// Instructor: Kavil Jain
// Project 2: Staged Opponet Avoidance Problem : Exhausetive Search Method
//
// Description:
//      This algorithm calculates the total number of valid paths in a 2D grid
//      from the top-left to the bottom-right corner while avoiding blocked 
//      cells.
//      Paths are found using binary sequences to encode allowed moves 
//      (right or down) and validated for grid bounds, obstacles, and reaching 
//      the goal. The exhaustive search has exponential complexity (O(n * 2^n)).  
//
/*
GIVEN GRID:

                ......X.X
                X........
                ...X...X.
                ..X....X.
                .X....X..
                ....X....
                ..X.....X
                .........
*/
//                
// ============================================================================




#include <iostream>
#include <vector>

using namespace std;

// function prototypes

int PathExhaustive(const vector<vector<char>> &grid);
bool isValidPath(const vector<vector<char>> &grid, int bits, int requiredMoves, 
                 int rows, int cols);

// ==== main ===================================================================
//
// Description:
//      Main function initializes the given problem grid and tests the 
//      PathExhaustive function to calculate the total number of valid paths
//      for the staged opponent avoidance problem. It prints the result to the 
//      console. Given case should be 102.
//
//      The provided grid can be replaced or commented out for testing with
//      other custom grids.
//
// Output:
//      Prints the total number of valid paths for the given grid.
//  
// ============================================================================


int main()
{
    vector<vector<char>> stagedGrid =  
    {
        {'.', '.', '.', '.', '.', '.', 'X', '.', 'X'},
        {'X', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.', 'X', '.'},
        {'.', '.', 'X', '.', '.', '.', '.', 'X', '.'},
        {'.', 'X', '.', '.', '.', '.', 'X', '.', '.'},
        {'.', '.', '.', '.', 'X', '.', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', '.', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'}
    };
    
    int validPaths = PathExhaustive(stagedGrid);
    
    std::cout << "\nAmount of valid paths for the given grid is " << validPaths;

	return 0;
}



// ==== PathExhaustive() ======================================================
//
// Input:
//      grid: A 2D vector of characters representing the grid. '.' is a
//            passable cell, and 'X' is a blocked cell.
//
// Output:
//      An integer value of the total number of valid paths from the
//      start to goal of the grid while avoiding blocked cells.
//  
// ============================================================================

int PathExhaustive(const vector<vector<char>> &grid)
{
    
    int rows = grid.size();         //get amt of rows in grid
    int cols = grid[0].size();      //get amt of cols in grid 
    
    int requiredMoves = rows + cols - 2;   //Total moves len =  r + c - 2 
    
    int pathCounter = 0;            //used as running count of valid paths
    
    char startCell = grid[0][0];              //holds contents of start cell
    char endCell = grid[rows - 1][cols - 1];  //holds contents of end cell(goal)
    
    //Case: start or end cell is blocked, return 0. No valid paths exist.
    if (startCell == 'X' || endCell == 'X')
    {
        return 0;
    }
    
    //Exhausive Search: Iterate through all possible bit combinations
    for (int bits = 0; bits < (1 << requiredMoves); bits++)
    {
        if (isValidPath(grid, bits, requiredMoves, rows, cols))
        {
            pathCounter++;
        }
    }
    
    return pathCounter;     //return total amount of valid paths 
   
}




// ==== isValidPath() ======================================================
//
// Input:
//      grid: A 2D vector of characters representing the grid. '.' is a
//            passable cell, and 'X' is a blocked cell.
//      bits: An integer encoding a candidate path as a binary sequence of moves.
//      requiredMoves: The total number of moves required to reach the goal.
//      rows: The number of rows in the grid.
//      cols: The number of columns in the grid.
//
// Output:
//      A boolean value that indicated whether the candidate path is valid. 
//      A valid path:
//              stays within bounds, avoids blocked cells, and ends at the goal.
//  
// ============================================================================

bool isValidPath(const vector<vector<char>> &grid, int bits, int requiredMoves, 
                 int rows, int cols)
{
    //Will be used to keep track of current visting coordinates. 
    //Starts at (0,0) "Top-Left of Grid"
    int currentRow = 0;
    int currentCol = 0;
    
    //Decode binary and check path validity
    for (int index = 0; index < requiredMoves; index++)
    {
        //Current index is 1: move right 
        if ((bits >> index) & 1)
        {
            currentCol++;
        }
        //Current index is 0: move down
        else
        {
            currentRow++;
        }
        
        //Check to make sure we are within bounds and avoid blocked cells
        if (currentRow >= rows || currentCol >= cols 
            || grid[currentRow][currentCol] == 'X')
        {
            
            return false; //invalid path
        }
    }
    
    //Make sure path has reached goal
    //Current cooridantes should be at (r-1,c-1)
    return (currentRow == rows - 1 && currentCol == cols - 1);
}

