#include <ctime>
#include <iostream>
#include <cmath>
#include "../palindrome.h"

using namespace std;

void test(const int n, const int b, const bool expected)
{
  int m = log(n) / log(b);
  cout << n << "_" << b << ": " << isBasePalindrome(n, b, m) << " --- expected: " << expected << endl;
}

int main (int argc, char* argv[])
{
  // Calculate...
  int sum = 0;
  for (int i = 0; i < 1000000; i++)
    if (isPalindrome(i, log10(i)) &&
        isBasePalindrome(i, 2, log(i) / log(2)))
      sum += i;

  cout << sum << endl;
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
