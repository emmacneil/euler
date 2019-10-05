#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

bool isPandigital(int a, int b, int c)
{
  int CHECKSUM = 1022; // binary 00000011 11111110
  int check = 0;

  while (a > 0) { check |= 1 << (a % 10); a /= 10; }
  while (b > 0) { check |= 1 << (b % 10); b /= 10; }
  while (c > 0) { check |= 1 << (c % 10); c /= 10; }

  return check == CHECKSUM;
}

bool isUnusual(const int n)
{
  const int SQRTN = sqrt(n);

  // Find each divisor of n...
  for (int i = 1; i <= SQRTN; i++)
  {
    // check if i divides n
    if (n % i == 0)
    {
      int k = n / i;
      if (isPandigital(n, k, i))
        return true;
    }
  }
  return false;
}

int main (int argc, char* argv[])
{
  // Calculate...
  int sum = 0;

  // Only need to consider 4 digit numbers
  for (int n = 1234; n <= 9876; n++)
    if (isUnusual(n))
      sum += n;

  // Output...  
  cout << sum << endl;
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
