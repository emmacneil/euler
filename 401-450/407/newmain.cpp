/*
 * Project Euler - Problem 407
 * Idempotents
 *
 * After doing a brute-force calculation on the first hundred values of M(n),
 * I've noticed that if n is a prime power, then M(n) = 1. Otherwise, let
 * n = p1^k1 p2^k2 ... pt^kt be the prime factorization of n, and let pi^ji be
 * the largest term in the factorization. I've observed that M(n) is always
 * either a multiple of pi^ji or one plus a multiple of pi^ji (note that this
 * still holds when n is itself a prime power).
 *   For example, take n = 24. Then n = (2^3)(3^1). The largest p^k term is 2^3
 * since 2^3 > 3^1. It turns out that M(24) = 16 = 2(2^3), a multiple of 2^3.
 *   Or take n = 14. Then n = (2^1)(7^1) and M(14) = 8 = 1(7^1) + 1, a multiple
 * of 7^1, plus one.
 *   So, the solution here is to calculate the largest prime power factor of
 * every integer from 2 to 10,000,000 (applying dynamic programming). Then,
 * when solving for M(n), let pk be the largest prime power factor of n, and
 * let a = n - pk. Check if the following equations hold true
 *
 *                             (a+1)^2 = a+1  mod n
 *                                 a^2 = a    mod n
 *
 * and return a+1 or a, depending on which one evaluated to true. Of course, if
 * they were both solutions, we keep a+1. If neither were true, we subtract
 * another pk from a and repeat.
 *   Multi-threading was used here to speed up the calculations.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const long BOUND = 10000000;
const bool OUTPUT = false;
const int  N_THREADS = 4;
const int  N_PER_THREAD = 100000;

int M[BOUND+1] = {0};
int largestFactor[BOUND+1] = {0};
vector<int> primes;

mutex range_mtx, result_mtx;



// Calculates the largest prime power factor of N.
// Stores the result in the largestFactor[] array.
// Also returns the result.
int getLargestFactor(const int N)
{
  int rootn = sqrt(N);
  int n = N, p = 0, pk;
  for (int i = 0; p <= rootn; i++)
  {
    // Find the first prime number which divides N.
    p = primes[i];
    if (N % p == 0)
    {
      // Calculate the largest power of this prime which divides N.
      pk = 1;
      while (n % p == 0)
      {
        pk *= p;
	n /= p;
      }
      // let N = p1^k1 p2^k2 ... pt^kt
      // We have just found p1^k1. We want to store either p1^k1 or the largest
      // term in p2^k2 ... pt^kt, whichever is larger.
      largestFactor[N] = max(largestFactor[N/pk], pk);
      return largestFactor[N];
    }
  }

  // If we reach this point, then N was a prime number.
  largestFactor[N] = N;
  return largestFactor[N];
}



// Solves for M(n).
int solve(int n)
{
  // M(0) and M(1) = 0
  if (n < 2) return 0;

  int pk = getLargestFactor(n);
  
  // If n is a prime power, M(n) = 1
  if (pk == n) return 1;

  // Let a be the largest multiple of pk less than n
  // If a+1 is a solution, return a+1
  // Otherwise, if a is a solution, return a.
  // Otherwise, subtract pk from a (thereby trying the next largest multiple
  //   of pk less than n) and try again.
  long a;
  int  m = n - pk;
  while (m > 0)
  {
    a = m + 1;
    if ( (a*a) % n == a ) return a;
    
    a = m;
    if ( (a*a) % n == a ) return a;

    m -= pk;
  }

  // We don't actually reach this point for the first 10,000,000 values of n.
  if (OUTPUT) cout << "Solution not found! ( M(" << n << ") )" << endl;

  return 0;
}



// The function run by each thread. Grabs a subset of the range [1, BOUND] and
// calculates M(n) for each number in that range. Threads run until every
// subset of the range has been calculated.
void run(int *start, int *end, long *result)
{
  int a, b;
  long n;

  range_mtx.lock();
  while (*start < BOUND)
  {
    // Find the next subset of [1, BOUND] that needs to be calculated
    a = *start;
    b = *end;
    *start += N_PER_THREAD;
    *end   += N_PER_THREAD;
    range_mtx.unlock();

    // Run calculations for each number in that range
    n = 0;
    for (int i = a; i <= b; i++)
      n += solve(i);
    
    // Record the results
    result_mtx.lock();
    *result += n;
    result_mtx.unlock();
    
    range_mtx.lock();
  }
  range_mtx.unlock();
}



int main(int argc, char *argv[])
{
  int start, end;
  long n;
  bool threading = false;
  thread threads[N_THREADS];

  if (argc > 1)
    if (argv[1][0] == '-')
      if (argv[1][1] == 't')
        threading = true;

  if (OUTPUT) cout << "BOUND = " << BOUND << endl;

  if (OUTPUT) cout << "Generating primes" << endl;
  genPrimes(&primes, BOUND);

  if (OUTPUT) cout << "Factorizing" << endl;
  for (int i = 2; i <= BOUND; i++)
    getLargestFactor(i);


  if (OUTPUT) cout << "Solving" << endl;
  n = 0;
  if (threading)
  {
    start = 1;
    end = N_PER_THREAD;
    for (int i = 0; i < N_THREADS; i++)
      threads[i] = thread(run, &start, &end, &n);
  
    for (int i = 0; i < N_THREADS; i++)
      threads[i].join();
  }
  else
  {
    for (int i = 1; i <= BOUND; i++)
      n += solve(i);
  }

  cout << n << endl;

  return 0;
}
