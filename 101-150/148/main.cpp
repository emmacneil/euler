/* Project Euler - Problem 148
 * Exploring Pascal's Triangle
 *
 * I had an earlier solution that ran in about 20 seconds, but this solution based on
 * 
 *                 http://cjordan.github.io/2013/12/29/solving-project-euler-148/
 *
 * is much nicer and terminates in milliseconds.
 */



#include <iostream>
using namespace std;

const unsigned long BOUND = 1000000000;

// n-th triangular number
unsigned long T[] = {0, 1, 3, 6, 10, 15, 21, 28};//, 36, 45, 55};

int main(int argc, char * argv[])
{
  unsigned long B = BOUND;
  unsigned long x = 0;
  unsigned long pow28 = 1;
  int d;

  while (B > 0)
  {
    d = B % 7;
    B /= 7;
    x = T[d] * pow28 + x * (d + 1);
    pow28 *= 28ul;
  }
  cout << x << endl;

  return 0;
}
