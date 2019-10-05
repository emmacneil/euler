#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

int p (const int n) { return n*(3*n-1)/2; }
//int abs (const int n) { return n > 0 ? n : -n; }

bool isp(const int n)
{
  for (int i = sqrt((2*n)/3); i*(3*i-1) <= 2*n; i++)
    if (i*(3*i-1) == 2*n)
      return true;
  return false;
}

int main (int argc, char* argv[])
{
  // Calculate...
  int sum, diff;
  for (int j = 1; j < 10000; j++)
  {
    for (int k = j + 1; k < 10000; k++)
    {
      sum  = p(j) + p(k);
      diff = abs( p(j) - p(k) );
      if ( isp(sum) && isp(diff) )
      {
        cout << "(" << j << ", " << k << ")   ";
        cout << "D = " << diff << endl;
      }
    }
  }
  
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
