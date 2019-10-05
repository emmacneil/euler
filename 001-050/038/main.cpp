#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

bool isPandigital(int n)
{
  int check = 0;
  while (n > 0) { check |= 1 << (n%10); n /= 10; }
  return check == 1022; // 1022 = binary 00000011 11111110
}

int main (int argc, char* argv[])
{
  // Calculate...
  // Only have to look at numbers with less than 5 digits (<10000)
  int p, max = 0;
  for (int k = 1; k < 10000; k++)
  {
    p = 0;
    for (int n = 1; n < 10 && p < 100000000; n++)
    {
      p *= pow(10, 1+(int)log10(k*n));
      p += k*n;
    }
    if (p < 1000000000)
      if (isPandigital(p))
        max = p > max ? p : max;
  }
  
  cout << max << endl;
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
