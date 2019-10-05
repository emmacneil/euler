/* Project Euler - Problem 209
 * Circular Logic
 *
 * Let F be the function
 *
 *                               F : {0,1}^6 --> {0,1}^6
 *                               F(a,b,c,d,e,f) = (b,c,d,e,f,a^(b&c))
 *
 * This function has 6 orbits. Given that 6 bits define an integer in the range [0,63], these
 * orbits are the cycles beginning with the integers 0, 1, 3, 5, 9, and 21. These cycles have
 * lengths 1, 6, 46, 6, 3, and 2, respectively.
 *   Let T denote a truth table, T : {0,1}^6 --> {0,1}. The problem is asking for the number
 * of truth tables satisfying T(n) & T(F(n)) = 0 for all integers in [0,63]. This imposes the
 * constraint that if T(n) = 1, then T(F(n)) = 0. This means that T cannot assign a 1 to two
 * consecutive integers in an orbit. The solution, then: for each orbit, count the number of
 * ways of assigning the values 0 or 1 to its elements without assigning 1's to any two adjacent
 * elements. Then we take the product of the 6 counts.
 *   The number of ways of placing 0's and 1's in a circle with no two consecutive 1's is closely
 * related to another problem -- counting the number of bit strings with no two consecutive 1's.
 * The number of bit strings of length n with no two consecutive 1's is known to be fib(n+2),
 * where fib(n) is the n-th Fibonacci number. (See OEIS A000045. This also arises in Project
 * Euler problem 301.) The number of cycles of length n with no two consecutive 1's is
 * fib(n+1) + fib(n-1). However, this is just the n-th Lucas number. Thus, we compute
 *
 *                                         product L(n)
 *                                         {n in C}
 *
 * where C = {1, 6, 46, 6, 3, 2}.
 */



#include <iostream>



/* If n is the 6-bit binary string pqrstu, then F(n) is the string qrstuv, where
 *
 *                                        v = p XOR (q AND r)
 *
 * This is not needed in the final solution, but was used to determine the orbits of F.
 */
unsigned char F(unsigned char n)
{
  unsigned char p, q, r, v;
  p = (n & 0x20) >> 5;
  q = (n & 0x10) >> 4;
  r = (n & 0x08) >> 3;
  v = p ^ (q & r);
  return ((n << 1) | v) & 0x3f;
}



int main(int argc, char * argv[])
{
  unsigned long count = 1UL;
  int C[] = {1, 6, 46, 6, 3, 2};
  unsigned long L[47];

  // Compute Lucas numbers up to L(46)
  L[0] = 2UL;
  L[1] = 1UL;
  for (int i = 2; i < 47; i++)
    L[i] = L[i-1] + L[i-2];

  for (int i = 0; i < 6; i++)
    count *= L[C[i]];
  
  std::cout << count << std::endl;
  
  return 0;
}
