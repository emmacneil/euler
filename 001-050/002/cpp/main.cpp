/* Project Euler - Problem 002
 * Even Fibonacci Numbers
 *
 * Every third Fibonacci number is even, and no others. We need only compute
 *
 *                             F(0) + F(3) + F(6) + ...
 *
 * until terms in this series exceed 4,000,000.
 */

#include <cstdint>
#include <iostream>

int main(int argc, char * argv[])
{
  uint64_t bound = 4000000;
  uint64_t f1 = 1;
  uint64_t f2 = 2;
  uint64_t sum = 0;
  
  if (argc == 2)
    bound = atoi(argv[1]);

  while (f2 < bound)
  {
    sum += f2;
    f2 = f2 + f1;
    f1 = f2 - f1;
    f2 = f2 + f1;
    f1 = f2 - f1;
    f2 = f2 + f1;
    f1 = f2 - f1;
  }

  std::cout << sum << std::endl; 

  return 0;
}
