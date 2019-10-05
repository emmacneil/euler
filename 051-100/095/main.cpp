/*
 * Project Euler - Problem 95
 * Amicable Chains
 *
 * Compute the sum of the divisors (sigma(n)) of every number from 1 to
 * 1,000,000. Then, for each n from 1 to 1,000,000, we hop from n to sigma(n)
 * to simga(sigma(n)) etc. until we reach n again (but set a limit on how
 * deeply we recurse). Just keep track of the longest chain and print out the
 * first number to give us that chain.
 */

#include <cmath>
#include <iostream>
#include <list>

using namespace std;

const bool OUTPUT    = false;
const int  BOUND     = 1000000;
const int  MAX_DEPTH = 100;

int dsum[BOUND+1] = {0};



int divisor_sum(const int N)
{
  if (dsum[N]) return dsum[N];

  const int sqrtn = sqrt(N);
  int n = N;

  for (int i = 2; i <= sqrtn; i++)
  {
    if (n % i == 0)
    {
      int pk = i;
      while (n % i == 0)
      {
        n /= i;
	pk *= i;
      }
      dsum[N] = dsum[n] * (pk - 1) / (i - 1);
      return dsum[N];
    }
  }

  dsum[N] = N + 1;
  
  return dsum[N];
}



int chain_length(int index, int start, int depth)
{
  if (depth == 0)
    return 0;
  if (index > BOUND)
    return 0;

  if (dsum[index] == start)
    return 1;

  int n = chain_length(dsum[index], start, depth-1);
  
  return n > 0 ? n + 1 : 0;
}



void print_chain(int index, int start)
{
  cout << index << " --> ";
  if (dsum[index] == start)
  {
    cout << start << endl;
    return;
  }
  print_chain(dsum[index], start);
}



int main()
{
  dsum[0] = 0;
  dsum[1] = 1;
  for (int i = 2; i <= BOUND; i++)
    divisor_sum(i);
  for (int i = 2; i <= BOUND; i++)
    dsum[i] -= i;

  int k = 0, m = 0, n;
  
  // Find the longest amicable chain.
  for (int i = 2; i <= BOUND; i++)
  {
    n = chain_length(i, i, MAX_DEPTH);
    if (n > m)
    {
      m = n;
      k = i;
    }
  }

  if (OUTPUT) print_chain(k, k);

  // Print the shortest element in the chain
  cout << k << endl;
  
  return 0;
}
