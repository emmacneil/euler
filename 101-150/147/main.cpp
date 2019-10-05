/* Project Euler - Problem 147
 * Rectangles in Cross-Hatched Grids
 * 
 * This is a dynamic programming problem. We can consider separately the number of rectangles on
 * a m X n grid oriented horizontally/vertically and oriented diagonally. Here we will define
 * f(m, n) to be the number of rectangles oriented orthogonally on a m X n grid, and g(m, n) to be
 * the number of rectangles oriented diagonally on a m X n grid.
 *   The number of rectangles oriented orthogonally on a m X n grid is equal to the number or
 * rectangles occupy the grid space (m, n), plus the number of rectangles that fit in a (m-1) X n
 * or m X (n-1) grid, minus the number that fit in a (m-1) X (n-1) grid, which we've just double
 * counted. There are mn rectangles that may occupy the the space (m, n), so we get
 *
 *                     f(m, n) = mn + f(m - 1, n) + f(m, n - 1) - f(m - 1, n - 1)
 *
 *   The diagonal case is more complicated. g(m, n) is still related to g(m - 1, n), g(m, n - 1),
 * g(m - 1, n - 1) in the same way f was, but we must add a term reflecting the number of
 * rectangles introduced by adding the m-th row and n-th column -- there are some rectangles that
 * are introduced, but do not occupy the space (m, n). We are interested in the number of rectangles
 * that occupy simultaneously the m-th row and n-th column, even if they do not occupy the space
 * (m, n). After some tinkering around I have found the following:
 *   If m < n, then there are
 *   
 *                  (2m - 1) + (2m - 2) + (2m - 2) + (2m - 3) + (2m - 3) ... + 1 + 2
 *
 * Let T(k) be the k-th triangular number. Then this is
 *
 *                                       T(2m - 1) + T(2m - 2)
 *
 *   If n < m, then we replace m with n.
 *   If m == n, we have the same result, but we have over counted by m.
 *   So we define
 *
 *            g(m, n) = T(k) + T(k - 1) - c + g(m - 1, n) + g(m, n - 1) + g(m - 1, n - 1)
 *
 *   where k = min(2m - 1, 2n - 1), and c = m if m = n, otherwise 0.
 */



#include <iostream>
using namespace std;



const bool OUTPUT = true;
const bool PRINT_MAT = false;
const unsigned int N_ROWS = 43;
const unsigned int N_COLS = 47;
unsigned int F[N_ROWS + 1][N_COLS + 1] = {0};
unsigned int G[N_ROWS + 1][N_COLS + 1] = {0};



void print_matrix(unsigned int M[N_ROWS + 1][N_COLS + 1])
{
  for (unsigned int r = 0; r <= N_ROWS; r++) {
    for (unsigned int c = 0; c <= N_COLS; c++)
      cout << M[r][c] << "\t";
    cout << endl;
  }
}



// Returns the n'th triangular number
unsigned int tri(unsigned int n)
{
  return (n * n + n) / 2;
}



// Returns the number of orthogonally oriented rectangles on an m x n grid.
unsigned int f(unsigned int m, unsigned int n)
{
  if (F[m][n]) return F[m][n];

  if ( (m < 1) || (n < 1) ) return 0;

  if (m == 1) return (F[m][n] = tri(n));
  if (n == 1) return (F[m][n] = tri(m));

  return (F[m][n] = m * n + f(m - 1, n) + f(m, n - 1) - f(m - 1, n - 1));
}



// Returns the number of diagonally oriented rectangles on an m x n grid.
unsigned int g(unsigned int m, unsigned int n)
{
  if (G[m][n]) return G[m][n];

  if ( (m < 1) || (n < 1) ) return 0;

  if (m == 1) return (G[m][n] = n - 1);
  if (n == 1) return (G[m][n] = m - 1);

  //unsigned int k, l;
  unsigned int c, k;

  //l = 2 * (m < n ? m : n) - 2;
  //k = 2 * tri(l) + l + 1;
  //if (m == n) k -= m;
  k = (m < n ? (2*m - 1) : (2*n - 1));
  c = (m == n ? m : 0);

  return (G[m][n] = tri(k) + tri(k - 1) - c +  g(m - 1, n) + g(m, n - 1) - g(m - 1, n - 1));
}



int main(int argc, char * argv[])
{
  unsigned int n = 0;

  // Count our sum.
  for (int r = 1; r <= N_ROWS; r++)
    for (int c = 1; c <= N_COLS; c++)
      n += f(r, c) + g(r, c);

  // Test output
  if (PRINT_MAT) {
    cout << "F[][]:" << endl;
    print_matrix(F);

    cout << endl << "G[][]" << endl;
    print_matrix(G);

    cout << endl;
  }  

  // Verbose output
  if (OUTPUT) {
    cout << f(N_ROWS, N_COLS) + g(N_ROWS, N_COLS) << " rectangles on a " << N_COLS << " X " << N_ROWS << " grid." << endl;
    cout << F[N_ROWS][N_COLS] << " orthogonal." << endl;
    cout << G[N_ROWS][N_COLS] << " diagonal." << endl;
  }

  // Solution output
  cout << n << endl;
}
