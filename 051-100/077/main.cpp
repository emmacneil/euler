/*
 * A modification of the change-making problem.
 */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "/home/evan/code/euler/include/primes.h"

using namespace std;

long count(const vector<int> *c, const int n, const int m)
{
  if (n == 0) return 1;
  if (n <  0) return 0;
  if (m <  0 
   && n >= 1) return 0;
  return count(c, n, m - 1) + count(c, n - (*c)[m], m);
}

int main(int argc, char *argv[])
{
  int m, n = 71; // Trial and error has shown 71 the solution.
  if (argc == 2)
    n = atoi(argv[1]);

  vector<int> coins;
  genPrimes(&coins, n);
  m = coins.size() - 1;

  cout << count(&coins, n, m) << endl;

  return 0;
}
