#include <ctime>
#include <iostream>

using namespace std;



int p[] = {1, 2, 3, 5, 7, 11, 13, 17};



bool ispand(long long n)
{
  int b, d, m = 0;
  while (n > 0)
  {
    d = n % 10; // Get last digit of n
    b = 1 << d;
    if ((m & b) == b) // if d has been encountered before
      return false;
    m |= b;
    n = n / 10;
  }
  return true;
}



long long f(const long long n, const int d)
{
  // Check if last three digits of n are divisible by p[d]
  if ((n % 1000) % p[d] > 0)
    return 0;

  // Check if n is, so far, pandigital
  if (!ispand(n))
    return 0;

  // d = 7 -> n contains the digits 0 through 9
  // Furthermore, it satisfies all conditions.
  if (d == 7)
    return n;

  long long sum = 0;
  for (int i = 0; i < 10; i++)
    sum += f(n*10+i, d+1);

  return sum;
}



int main (int argc, char* argv[])
{
  long long sum = 0;
  for (int i = 102; i < 988; i++)
    sum += f(i, 0);
  cout << sum << endl;

  return 0;
}
