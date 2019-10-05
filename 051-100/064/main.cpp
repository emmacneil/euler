// Problem 64: Odd Period Square Roots

#include <iostream>

using namespace std;



const int N = 10000;
const bool OUTPUT = false;



int period(const int s, const int sqrt_s)
{
  if (sqrt_s * sqrt_s == s)
  {
    if (OUTPUT)
      cout << "[" << sqrt_s << "]" << endl;
    return 0;
  }

  if (OUTPUT)
    cout << "[" << sqrt_s << ";(";

  int p = 0;
  int m0 = 0;
  int d0 = 1;
  int a0 = sqrt_s; //1
  int m1 = a0 * d0 - m0; //1
  int d1 = (s - m1*m1) / d0; //1
  int a1 = (sqrt_s + m1) / d1; //2
  int m = m0 = m1; //1
  int d = d0 = d1; //1
  int a = a0 = a1; //2
  m1 = d1 = a1 = -1;

  while ( (m1 != m) || (d1 != d) || (a1 != a) )
  {
    if (OUTPUT)
    {
      if (p == 0)
        cout << a0;
      else
        cout << "," << a0;
    }
    m0 = m1 = a0 * d0 - m0; // 3
    d0 = d1 = (s - m1*m1) / d0; //
    a0 = a1 = (sqrt_s + m1) / d1;
    p++;
  }
  
  if (OUTPUT)
    cout << ")]" << endl;
  
  return p;
}

int main()
{
  int sqrt_i = 1;
  int cnt = 0;
  for (int i = 1; i <= N; i++)
  {
    if (i >= (sqrt_i+1) * (sqrt_i+1))
      sqrt_i++;
    if (period(i, sqrt_i) % 2)
      cnt++;
  }
  cout << cnt << endl;

  return 0;
}
