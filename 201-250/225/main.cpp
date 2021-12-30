/* Project Euler - Problem 225
 * Tribonacci non-divisors
 *
 * To determine if some integer m divides a term in the Tribonacci sequence, we compute the sequence
 * modulo m. For example, when m = 7, we have the sequence
 *
 *     1, 1, 1, 3, 5, 2, 3, 3, 1, 0, ...
 *
 * The presence of a 0 means there is a term divisible by 7. Moreover, if we keep going, we get
 *
 *     1, 1, 1, 3, 5, 2, 3, 3, 1, 0, 4, 5, 2, 4, 4, 3, 4, 4, 4, 5, 6, 1, 5, 5, 4, 0, 2, 6, 1, 2, 2,
 *     5, 2, 2, 2, 6, 3, 4, 6, 6, 2, 0, 1, 3, 4, 1, 1, 6, 1, 1, 1, ...
 *
 * After which point the sequence repeats. Given any modulus, the sequence will eventually return to
 * 1, 1, 1 and repeat. Therefore, an approach is to reduce the Tribonacci sequence modulo
 * increasingly large odd numbers, stopping the sequence if we encounter a 0 or three 1's. Output
 * the 124'th odd integer for which we do not encounter a 0. The numbers are small enough that this
 * takes only milliseconds to compute.
 */

#include <cstdlib>
#include <iostream>

bool test(int m);

int main(int argc, char *argv[])
{
    int m = 1, count = 0, target = 124;
    if (argc == 2) target = atoi(argv[1]);
    while (count < target)
        if (test(m = m + 2)) count++;
    std::cout << m << std::endl;
    return 0;
}

// Returns true if no term in the Tribonacci sequence is divisible by m.
bool test(int m)
{
    int a = 1, b = 1, c = 1;
    do {
        int tmp = a + b + c;
        a = b; b = c; c = tmp % m;
        if (c == 0) return false;
    } while(a != 1 || b != 1 || c != 1);
    return true;
}
