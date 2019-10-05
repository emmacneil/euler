/**
 * Project Euler - Problem 126
 * Cuboid Layers
 *
 * For a cuboid of dimensions m x n x q, the number of blocks in the l'th layer
 * is equal to
 *
 *             2(mn + mq + nq) + 4(l - 1)(m + n + q) + 8 tri(l - 2)
 *
 * where tri(n) is the n'th triangular number.
 *   For each cuboid with at most some specified amount of blocks, compute the
 * number of blocks in each layer, until the number of blocks in a layer
 * exceeds that specified amount. We just need to make a reasonable guess for
 * what that amount should be.
 *   If some layer contains K blocks, we increase the K'th element of some
 * array by 1. Then we look for the first occurrence of 1000 in that array.
 */

#include <iostream>

using namespace std;



// Maximum number of blocks permitted in a layer
const int BOUND = 200000;
const int TARGET = 1000;
int C[BOUND + 1] = {0};



// Returns the n'th triangular number, or 0 for n < 1.
int tri(int n)
{
  return n > 0 ? (n*n + n)/2 : 0;
}



// Returns the number of blocks in the l'th layer around a cuboid with
// dimensions m x n x q
int f(int m, int n, int q, int l)
{
  return 2*(m*n + m*q + n*q)
       + 4*(l-1)*(m + n + q)
       + 8*tri(l-2);
}



int main(int argc, char * argv[])
{
  int blocks, i, layer;

  for (int m = 1; m <= BOUND; m++)
  {
    for (int n = 1; n <= m && m * n <= BOUND; n++)
    {
      for (int q = 1; q <= n && m * n * q <= BOUND; q++)
      {
        layer = 1;
	blocks = f(m, n, q, layer++);
	while (blocks <= BOUND)
	{
          C[blocks]++;
	  blocks = f(m, n, q, layer++);
        }
      }
    }
  }

  i = 0;

  while (C[++i] != TARGET)
    continue;
  
  cout << i << endl;
  
  return 0;
}
