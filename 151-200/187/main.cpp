/* Project Euler - Problem 187
 * Semiprimes
 *
 * Let q and r be prime numbers, not necessarily distinct, but with q <= r. If qr < 10^8, then so
 * too is pr < 10^8 for every prime number p < q. This forms the basis for an algorithm counting
 * semiprimes under 10^8.
 *     Initialize q to be the largest prime less than (10^8)/2 and p = 2. Then pq is the largest
 * semiprime under 10^8. Then we repeat the following:
 * 
 *     (i)   p := the largest prime such that pq < 10^8
 *     (ii)  Count the number of primes less than or equal to p and add it to a running total
 *     (iii) q := the prime number before the current value of q
 * 
 * After precomputing a list of primes, this process can be done in linear time. We can also stop
 * the loop early once q < 10^4. At this point, the number of semiprimes with q as the largest
 * prime factor is simply the i-th triangular number, where q is the i-th prime number.
 */

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

std::vector<uint32_t> sieve(int n);

int main(int argc, char *argv[])
{
    uint32_t bound = 100000000;
    if (argc == 2) bound = atoi(argv[1]);

    std::vector<uint32_t> P = sieve(bound/2);

    uint32_t count = 0;
    size_t i = 0, j = P.size() - 1;
    while (i < j)
    {
        while (P[i+1]*P[j] < bound) i++;
        count += i + 1;
        j--;
    }
    count += (j + 1)*(j + 2)/2;

    std::cout << count << std::endl;

    return 0;
}

std::vector<uint32_t> sieve(int n)
{
    std::vector<uint32_t> ret;
    std::vector<bool>is_prime(n, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (uint32_t i = 2; i < n; i++)
        if (is_prime[i])
            for (uint32_t j = i + i; j < n; j += i)
                is_prime[j] = false;
    
    for (uint32_t i = 0; i < n; i++)
        if (is_prime[i])
            ret.push_back(i);
    
    return ret;
}