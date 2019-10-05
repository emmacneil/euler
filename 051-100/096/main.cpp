/*
 * Project Euler - Problem 96
 * Su Doku
 *
 * Use backtracking to find the solution to each Sudoku puzzle.
 */

#include <iostream>

using namespace std;

const bool OUTPUT    = false;
const int  N_PUZZLES = 50;



// Read a 9x9 puzzle from stdin
void read_puzzle(int arr[9][9])
{
  // Throw away "Grid XX"
  cin.ignore(256, '\n');
  
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      arr[i][j] = cin.get() - '0';
    cin.ignore(256, '\n');
  }
}



void output_puzzle(int arr[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      cout << arr[i][j];
    cout << endl;
  }
  cout << endl;
}



// Returns true if the value at (row, col) is not a duplicate of another value
// in the same row.
bool check_row(int arr[9][9], int row, int col)
{
  int n = 0;
  for (int i = 0; i < 9; i++)
    if (i == col) continue;
    else n |= 1 << arr[row][i];
  return ((1 << arr[row][col]) & n) == 0;
}



// Returns true if the value at (row, col) is not a duplicate of another value
// in the same column.
bool check_col(int arr[9][9], int row, int col)
{
  int n = 0;
  for (int i = 0; i < 9; i++)
    if (i == row) continue;
    else n |= 1 << arr[i][col];
  return ((1 << arr[row][col]) & n) == 0;
}



// Returns true if the value at (row, col) is not a duplicate of another value
// in the same 3x3 region.
bool check_box(int arr[9][9], int row, int col)
{
  int br = row / 3, bc = col / 3, n = 0;
  for (int i = br * 3; i < (br + 1) * 3; i++)
    for (int j = bc * 3; j < (bc + 1) * 3; j++)
      if (i == row && j == col) continue;
      else n |= 1 << arr[i][j];
  return ((1 << arr[row][col]) & n) == 0;
}



// Use backtracking to solve the puzzle instance.
bool solve_puzzle(int arr[9][9], int row, int col)
{
  if (row == 9)
    return true;

  if (arr[row][col]) return col == 8 ?
                            solve_puzzle(arr, row+1, 0) :
			    solve_puzzle(arr, row, col+1);
  for (int i = 1; i < 10; i++)
  {
    arr[row][col] = i;
    if ( check_row(arr, row, col) &&
         check_col(arr, row, col) &&
	 check_box(arr, row, col) )
    {
      bool b = col == 8 ?
               solve_puzzle(arr, row+1, 0) :
	       solve_puzzle(arr, row, col+1);
      if (b) return true;
    }
  }
  arr[row][col] = 0;
  return false;
}



int main()
{
  int arr[9][9];
  int n = 0;
  
  for (int i = 0; i < N_PUZZLES; i++)
  {
    read_puzzle(arr);
    solve_puzzle(arr, 0, 0);
    if (OUTPUT) output_puzzle(arr);
    n += arr[0][0] * 100 + arr[0][1] * 10 + arr[0][2];
  }

  cout << n << endl;
  
  return 0;
}
