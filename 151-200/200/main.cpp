/* Project Euler - Problem 200
 * Find the 200th prime-proof sqube containing the contiguous substring "200"
 *
 * The solution is simply to generate a list of all primes under some bound, then generate a list
 * of all squbes under some larger bound. Filter out from the list of squbes those that do not
 * contain the substring "200", sort the remaining, then find the 200th one that is prime proof.
 *   Based on an earlier failed attempt at this problem, I was able to determine that the solution
 * is at most a 12-digit number, i.e. less than a trillion. By generating all primes less than
 * one million, we can generate all squbes less than one trillion and also test all 12-digit
 * numbers for primality by trial division.
 */

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>



// Return a vector of all primes less than or equal to bound.
template <class T> typename std::enable_if<std::is_integral<T>::value, std::vector<T>>::type
prime_sieve(T bound)
{
  std::vector<bool> sieve(bound - 1, true);
  std::vector<T> ret;

  for (T i = 0; i < bound - 1; i++)
  {
    if (sieve[i])
    {
      T p = i + 2;
      ret.push_back(p);
      for (T j = i + p; j < bound - 1; j += p)
        sieve[j] = false;
    }
  }
  return ret;
}



bool is_prime(uint64_t n, std::vector<uint64_t> & primes)
{
  uint64_t p = 0;
  for (int i = 0; p*p <= n; i++)
  {
    p = primes[i];
    if (n % p == 0)
      return false;
  }
  return true;
}



// Returns false if changing any single digit in n would produce a prime number.
// Otherwise returns true.
bool is_prime_proof(uint64_t n, std::vector<uint64_t> & primes)
{
  // Find out number of digits D in n
  uint64_t scale = 1UL;
  int D = 0;
  while (scale < n)
  {
    scale *= 10UL;
    D++;
  }
  scale = 1UL;
  for (int d = 0; d < D; d++)
  {
    uint64_t N = (n / (scale*10UL))*(scale*10UL) + (n % scale);
    bool b = (!is_prime(N + 0*scale, primes)) &&
             (!is_prime(N + 1*scale, primes)) &&
             (!is_prime(N + 2*scale, primes)) &&
             (!is_prime(N + 3*scale, primes)) &&
             (!is_prime(N + 4*scale, primes)) &&
             (!is_prime(N + 5*scale, primes)) &&
             (!is_prime(N + 6*scale, primes)) &&
             (!is_prime(N + 7*scale, primes)) &&
             (!is_prime(N + 8*scale, primes)) &&
             (!is_prime(N + 9*scale, primes));
    if (!b)
      return false;
    scale *= 10UL;
  }
  return true;
}



// Returns true if the substring "200" appears in n.
// e.g. contains_200(12003) = true
//      contains_200(30021) = false
bool contains_200(uint64_t n)
{
  while (n > 199)
  {
    if (n % 1000 == 200) // If the last three digits are 200,
      return true;       // return true.
    n /= 10;             // Otherwise, lop off a digit.
  }
  return false;
}



int main(int argc, char * argv[])
{
  // Generate a list of primes uner 1,000,000.
  std::vector<uint64_t> primes = prime_sieve((uint64_t)1000000);
  uint32_t n_primes = primes.size();
  
  // Generate a list of all squbes under p^2, where p is the largest prime generated.
  // This is the list of all squbes that we can quickly factor using trial division by
  // all the primes we've just generated.
  // We can simultaneously filter out the squbes that do not contain "200" as a substring
  uint64_t BOUND = primes.back()*primes.back();
  std::vector<uint64_t> sqube_list(0);
  for (int i = 0; i < n_primes; i++)
  {
    uint64_t p = primes[i];
    for (int j = i + 1; j < n_primes; j++)
    {
      uint64_t q = primes[j];
      uint64_t s0, sqube1, sqube2;
      s0 = p*p*q*q;
      sqube1 = s0*p;
      sqube2 = s0*q;

      if (sqube1 >= BOUND)
        break;
      if ((sqube1 < BOUND) && contains_200(sqube1))
          sqube_list.push_back(sqube1);
      if ((sqube2 < BOUND) && contains_200(sqube2))
          sqube_list.push_back(sqube2);
    }
  }
  // Sort the list of squbes.
  std::sort(sqube_list.begin(), sqube_list.end());

  // Find 200th remaining sqube that is prime-proof
  uint64_t count = 0;
  for (uint64_t s : sqube_list)
  {
    
    
    if (is_prime_proof(s, primes)) // Check if s is prime proof.
      count++;                     // If so, add to count
    if (count == 200)              // If count reaches 200, print and stop
    {
      std::cout << s << std::endl;
      break;
    }
  }

  return 0;
}
