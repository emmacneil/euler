/*
 * Project Euler - Problem 71
 * Ordered Fractions
 *
 * For d <= 8, 2/5 is immediately to the left of 3/7
 * For d <= 12, 5/12 is immediately to the left
 * For d <= 19, it is 8/19.
 * Each 'new' value being inserted just left of 3/7 is of the form
 *   (3k - 1) / (7k - 2)
 * 999997 is the largest denominator of this form. Solve for k and the
 * numerator follows.
 */
#include <iostream>

using namespace std;

int main()
{
  int k = (999997 + 2) / 7;
  cout << 3 * k - 1 << endl;
  return 0;
}
