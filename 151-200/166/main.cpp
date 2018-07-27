/* Project Euler - Problem 166
 * Criss Cross
 *
 * Denote the entries in the 4x4 grid by the variables
 *
 *   [ a b c d ]
 *   [ e f g h ]
 *   [ i j k l ]
 *   [ m n p q ]
 *
 * Each variable is a single digit, so there are 10,000,000,000,000,000 possibilities. Testing all
 * of these is intractible. Using linear algebra, we can reduce the number of possibilities. Every
 * row and column and the diagonal and antidiagonal must sum up to the same number, N. This gives
 * us a system of equations,
 *
 *   N = a + b + c + d
 *   N = e + f + g + h
 *   N = ...
 *
 * and so on. We have more variables than equations, but we can reduce this system to
 *
 *   N =                    m + n + p + q
 *   a =   h         + l -  m
 *   b =   h - j + k + l -  m - n     + q
 *   c = - h + j - k - l + 2m + n
 *   d = - h         - l +  m + n + p
 *   e = - h + j + k
 *   f = - h     - k - l + 2m + n + p
 *   g =   h - j     + l -  m         + q
 *   i =     - j - k - l +  m + n + p + q
 *
 * We have 8 free variables, each taking on a value between 0 and 9, inclusive. This gives
 * 100,000,000 possible ways to assign digits to our 16 variables. We need only check that for each
 * assignment to the free variables, the bound variables (other than N) are between 0 and 9.
 *   We could replace N with a + b + c + d in the above equations, though this does not gain us
 * anything.
 */

#include <iostream>

using namespace std;

int count;



// Returns true if n is a non-negative single digit integer,
// i.e. if 0 <= n <= 9.
bool is_single_digit(int n) { return (n < 10) && (n > -1); }



// Given the 8 variables h, j, k, l, m, n, p, q, there is a unique 4x4 grid of numbers
//
//   [ a b c d ]
//   [ e f g h ]
//   [ i j k l ]
//   [ m n p q ]
//
// where every row, column, and diagonal adds up to the same value. We can solve for a, b, c, d,
// e, f, g, i in terms of the above 8 variables. This function returns true if the latter 8
// variables are all non-negative single digit integers.
bool check(int h, int j, int k, int l, int m, int n, int p, int q)
{
  int a =  h + l - m;
  int b =  h - j + k + l - m - n + q;
  int c = -h + j - k - l + m + m + n;
  int d = -h - l +  m + n + p;
  int e = -h + j + k;
  int f = -h - k - l + m + m + n + p;
  int g =  h - j + l - m + q;
  int i = -j - k - l + m + n + p + q;
  
  if (!is_single_digit(a)) return false;
  if (!is_single_digit(b)) return false;
  if (!is_single_digit(c)) return false;
  if (!is_single_digit(d)) return false;
  if (!is_single_digit(e)) return false;
  if (!is_single_digit(f)) return false;
  if (!is_single_digit(g)) return false;
  if (!is_single_digit(i)) return false;
  
  return true;
}



int main(int argc, char * argv[])
{
  count = 0;
  
  for (int h = 0; h < 10; h++)
  for (int j = 0; j < 10; j++)
  for (int k = 0; k < 10; k++)
  for (int l = 0; l < 10; l++)
  for (int m = 0; m < 10; m++)
  for (int n = 0; n < 10; n++)
  for (int p = 0; p < 10; p++)
  for (int q = 0; q < 10; q++)
    if (check(h, j, k, l, m, n, p, q))
      count++;
  
  cout << count << endl;
  
  return 0;
}
