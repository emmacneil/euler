/*
 * Project Euler - Problem 76
 * Counting Summations
 *
 * This is the same as asking in how many ways can 100 be partitioned, though
 * we exclude the trivial case {100}
 */

//#include "/home/evan/code/cpp/numbers/numbers.h"
#include "numbers.h"
#include <iostream>

using namespace std;

int main()
{
  cout << partitions(100) - 1 << endl;
  return 0;
}
