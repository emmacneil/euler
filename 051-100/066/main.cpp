// Problem 66 - Diophantine Equation

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

const bool OUTPUT = false;



vector<int> period(const int s, const int sqrt_s)
{
  vector<int> vec;
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
  vec.push_back(sqrt_s);
  while ( (m1 != m) || (d1 != d) || (a1 != a) )
  {
    vec.push_back(a0);
    m0 = m1 = a0 * d0 - m0; // 3
    d0 = d1 = (s - m1*m1) / d0; //
    a0 = a1 = (sqrt_s + m1) / d1;
  }
  
  return vec;
}

int128_t *minx(int128_t d, int128_t sqrt_d, vector<int> *vec)
{
  int128_t a0, a1, a2, b0, b1, b2;
  
  int len = vec->size();
  int k = 0;
  a0 = (*vec)[0];
  b0 = 1;
  a1 = 1 + (*vec)[0] * (*vec)[1];
  b1 = (*vec)[1];
  a2 = a1;
  b2 = b1;

  while (a2 * a2 - d * b2 * b2 != 1)
  {
    k++;
    a2 = (*vec)[1+k%(len-1)] * a1 + a0;
    b2 = (*vec)[1+k%(len-1)] * b1 + b0;
    a0 = a1;
    a1 = a2;
    b0 = b1;
    b1 = b2;
  }

  if (OUTPUT)
    cout << "(" << a2 << ")(" << a2 << ") - "
         << "(" << d  << ")(" << b2 << ")(" << b2 << ") = 1" << endl; 

  int128_t *ans = new int128_t;
  *ans = a2;

  return ans;
}

int main()
{
  vector<int> vec;
  long sq = 2, k = 0;
  int128_t n, m = 0;
  for (long d = 2; d <= 1000; d++)
  {
    // Avoid computing minx for perfect squares
    if (sq * sq == d)
    {
      sq++;
      continue;
    }

    vec = period(d, sq-1);
    n = *minx(d, sq-1, &vec);
    if (n > m)
    {
      m = n;
      k = d;
    }
  }
  //vec = period(13, 3);
  //for (int i = 0; i < vec.size(); i++) cout << vec[i] << ", "; cout << endl;
  //n = *minx(13, 3, &vec);
  //cout << n << endl;
  
  cout << k << endl;

  return 0;
}
