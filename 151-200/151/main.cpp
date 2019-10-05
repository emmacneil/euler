/* Project Euler - Problem 151
 * Paper Sheets of Standard Sizes: an Expected Value Problem
 *
 * Construct a probability tree. A node holds the value 1 if it reflects a state where there is
 * only one sheet in the envelope, otherwise 0. We add the sum of all nodes, multiplied by the
 * probability of reaching that node. The function f defined below is a recursive function
 * emulating descent into this probability tree.
 *   Memoization might improve the runtime, but this completes in milliseconds without it.
 */



#include <iostream>
using namespace std;



double f(int a1, int a2, int a3, int a4, int a5)
{
  int sheets = a1 + a2 + a3 + a4 + a5;
  if (sheets == 0) return 0.0;
  double ret = sheets == 1 ? 1.0 : 0.0;

  if (a1 > 0)
    ret += (double)a1 / (double)sheets * f(a1 - 1, a2 + 1, a3 + 1, a4 + 1, a5 + 1);
  if (a2 > 0)
    ret += (double)a2 / (double)sheets * f(a1, a2 - 1, a3 + 1, a4 + 1, a5 + 1);
  if (a3 > 0)
    ret += (double)a3 / (double)sheets * f(a1, a2, a3 - 1, a4 + 1, a5 + 1);
  if (a4 > 0)
    ret += (double)a4 / (double)sheets * f(a1, a2, a3, a4 - 1, a5 + 1);
  if (a5 > 0)
    ret += (double)a5 / (double)sheets * f(a1, a2, a3, a4, a5 - 1);
  return ret;
}



int main(int argc, char * argv[])
{
  // Subtract 2, since f() counts the first and last papers drawn, which is to be excluded as per
  // the problem statement.
  cout << f(1, 0, 0, 0, 0) - 2 << endl;
  return 0;
}
