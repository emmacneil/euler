#include <cmath>
#include <iostream>

using namespace std;

const bool output = false;
const int  BOUND  = 10000000;

int phi[BOUND] = {0};


bool permutation(int m, int n)
{
  int arr[10] = {0};
  
  while (m > 0)
  {
    arr[m % 10]++;
    m /= 10;
  }
  
  while (n > 0)
  {
    arr[n % 10]--;
    n /= 10;
  }
  
  for (int i = 0; i < 10; i++)
    if (arr[i])
      return false;

  return true;
}

int eulerphi(int n)
{
  if (n == 1)
    return 1;
  if (phi[n])
    return phi[n];

  const int SQRT_N = sqrt(n);
  int a = n, e = 0, m = 1;
  for (int i = 2; i <= SQRT_N; i++)
  {
    if (n % i == 0)
    {
      while (n % i == 0)
      {
        n /= i;
	e++;
      }
      for (int k = 1; k < e; k++)
        m *= i;
      m *= (i - 1);
      phi[a] = m * eulerphi(n);
      return phi[a];
    }
  }

  phi[n] = n - 1;
  return n - 1;
}

int main()
{
  int k, e;
  double mini = 2.0, d;

  for (int i = 2; i < BOUND; i++)
  {
    e = eulerphi(i);
    if (permutation(i, e))
    {
      if (output)
        cout << "(" << i << ", " << e << ")" << endl;
      
      d = (double)i / (double)e;
      if (d < mini)
      {
        mini = d;
	k = i;
      }
    }
  }

  cout << k << endl;

  return 0;
}
