/* Project Euler - Problem 251
 * Cardano Triplets
 *
 * A triplet of positive integers (a, b, c) is a Cardano triplet if it satisfies
 *
 *                         (a + b*sqrt(c))^(1/3) + (a - b*sqrt(c))^(1/3) = 1.
 *
 * By cubing both sides (noting that cubing and taking cube roots are mutually inverse operations
 * on positive real numbers) and applying a few other tricks, one can show that the above
 * equation holds if and only if
 *
 *                               8*a^3 + 15*a^2 + 6*a = 27*b^2*c + 1.
 * 
 * We can factor this as well,
 *
 *                                (8*a - 1)*(a + 1)^2 = 27*b^2*c.
 * 
 * A solution requires that a = 2 (mod 3), so let a = 3k + 2, k >= 0.
 * Then
 *
 *                                  (8k + 5)(k + 1)^2 = b^2*c
 *
 * The solution is to factor (8k + 5)(k + 1)^2 and count the number of ways we can separate out a
 * square term. Even easier is to factor (8k + 5) and (k + 1) individually, and then combine
 * their factorizations. Given that
 *                                a <= N = 110,000,000 
 *                                k <= (N - 2)/3 = 36,666,666,
 *
 * we need only a list of primes less than or equal to
 * 
 *                                17,126 = sqrt(8*k + 5).
 */

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

// Return a vector of all primes less than or equal to bound.
vector<int> prime_sieve(int bound)
{
  bool sieve[bound-1] = {};
  for (bool & b : sieve)
    b = true;
  vector<int> ret;
  for (int i = 0; i < bound - 1; i++)
  {
    if (sieve[i])
    {
      int p = i + 2;
      ret.push_back(p);
      for (int j = i + p; j < bound - 1; j += p)
        sieve[j] = false;
    }
  }
  return ret;
}

// Count the number of square divisors b of K = (8k + 5)(k + 1)^2
// given the constraint that a + b + c <= BOUND,
// where a = 3k + 2 and c = K/b^2
int count(const int k, const vector<int> & P, const int BOUND)
{
  const int a = 3*k + 2;
  // const int K = (8*k + 5)*(k + 1)*(k + 1);
  // Factor K.
  // If p^(2r + 1) is a factor of K, then multiply ret by (r + 1)
  int ret = 1;
  for (int p : P) // for every possible prime divisor of k
  {
    int r = 0;
    int k1 = 8*k + 5;
    int k2 = k + 1;
    while (k1 % p == 0)
    {
      r++;
      k1 /= p;
    }
    while (k2 % p == 0)
    {
      r += 2;
      k2 /= p;
    }
    if (r > 0)
      ret *= r/2 + 1;
  }
  return ret;
}

int main(int argc, char * argv[])
{
  const int A_BOUND = atoi(argv[1]);
  const int K_BOUND = (A_BOUND - 2)/3;
  const int P_BOUND = sqrt(8*K_BOUND + 5);
  int cnt = 0;
  vector<int> P = prime_sieve(P_BOUND);
  for (int k = 0; k <= K_BOUND; k++)
     cnt += count(k, P, A_BOUND);
  cout << cnt << endl;
  return 0;
}
