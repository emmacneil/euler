/* Project Euler - Problem 179
 * Consecutive Positive Divisors
 *
 * The number of positive divisors of a positive integer is determined by the exponents in its
 * prime factorization. For example, if
 * 
 *                         n = p_1^(k_1) * p_2^(k_2) * ... * p_m^(k_m),
 * 
 * then the number of positive divisors of n is (k_1 + 1)*(k_2 + 1)*...*(k_m + 1). Each prime
 * number has two positive divisors, and the divisors of composite numbers can be counted using
 * dynamic programming.
 *     Let s(n) be the number of positive divisors of n. Then s(p) = 2 for all primes p. Then we
 * iterate over all composite integers 4 <= n <= 10^7.
 *     To compute s(n) for a composite number n, find a prime divisor p of n. Let k be the largest
 * integer such that p^k divides n. Then s(n) = s(n/p)*(k+1)/k. Because s(n/p) is already known,
 * and by precomputing a list of primes, this can be computed quite quickly.
 *     Once s(n) is computed for all 1 < n < 10^7, it is easy to tell which neighbouring integers
 * have the same number of divisors.
 */

#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <vector>

const uint32_t BOUND = 10000000;
uint32_t memo[BOUND]{0};
std::vector<uint32_t> primes;

void count_divisors();
void count_divisors(uint32_t n);
void precompute_primes();

int main(int argc, char *argv[])
{
    precompute_primes();
    
    for (uint32_t p : primes)
        memo[p] = 2;

    count_divisors();

    int count = 0;
    for (int i = 1; i < BOUND; i++)
        if (memo[i] == memo[i-1])
            count++;

    std::cout << count << std::endl;

    return 0;
}

// Count the number of positive divisors of each positive integer 0 <= n < BOUND.
// Assumes these have already been counted for all primes p.
void count_divisors()
{
    memo[0] = 0; // These aren't relevant to the solution
    memo[1] = 1; // but let's define them anyway
    for (uint32_t i = 4; i < BOUND; i++)
    {
        count_divisors(i);
    }
}

// Count the number of positive divisors of n.
// Assumes this count has been done for all other integers 0 < m < n.
void count_divisors(uint32_t n)
{
    if (memo[n]) return;
    uint32_t n_cpy = n;
    uint32_t k = 0;
    for (uint32_t p : primes)
    {
        while (n % p == 0)
        {
            n /= p;
            k++;
        }
        if (k)
        {
            memo[n_cpy] = memo[n_cpy/p]/k*(k+1);
            return;
        }
    }
}

// Populates the (global) vector 'primes' using a prime number sieve
void precompute_primes()
{
    std::vector<bool>is_prime(BOUND, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (uint32_t i = 2; i < BOUND; i++)
        if (is_prime[i])
            for (uint32_t j = i + i; j < BOUND; j += i)
                is_prime[j] = false;
    
    for (uint32_t i = 0; i < BOUND; i++)
        if (is_prime[i])
            primes.push_back(i);
}