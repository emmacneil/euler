/* Project Euler - Problem 204
 * Generalised Hamming Numbers
 *
 * Straightforward. Just find all positive integers less than 10^9 of the form
 *
 * h = 2^a 3^b ... 97^y
 *
 * Start with a = b = ... = y = 0. Iteratively increase a by 1, adding 1 to the Hamming number
 * count each time, until this causes h to exceed 10^9. Then reset a to 0, and increase b by 1.
 * If increasing b by 1 ever causes h to exceed 10^9, reset it too to 0 and increase c by 1,
 * and so on. If increasing y ever causes h to exceed 10^9, then we are done counting.
 *   Maybe there is a faster recursive solution ...
 *
 * Compile with -std=c++11
 */

#include <iostream>
#include <vector>

using namespace std;



// Prime numbers less than 100
vector<long> p = {
             2,  3,  5,  7, 11,
             13, 17, 19, 23, 29,
             31, 37, 41, 43, 47,
             53, 59, 61, 67, 71,
             73, 79, 83, 89, 97};
const int N_PRIMES = p.size();



// Returns the product of all integers in the vector.
long product(vector<long> v)
{
  long ret = 1;
  for (long a : v)
    ret *= a;
  return ret;
}



// Returns the nu
int solve(const long N)
{
  vector<long> k(N_PRIMES,1);
  int ret = 0;
  
  while (true)
  {
    // Increase number of generalised Hamming numbers by 1.
    ret++;
    
    // Test output
    // cout << product(k) << endl;
    
    // Find next generalised Hamming number
    for (int i = 0; i < N_PRIMES; i++)
    {
      k[i] *= p[i];
      if (product(k) > N)
      {
        // If increasing the power of the largest permitted prime factor causes us to exceed N,
	// then stop counting.
        if (i == N_PRIMES - 1)
	  return ret;
        k[i] = 1;
      }
      else
        break;
    }
  }
}



int main(int argc, char * argv[])
{
  cout << solve(1000000000L) << endl;

  return 0;
}
