#include <iostream>
#include <map>

#define GOAL 5

using namespace std;

map<long, int> toCnt;
map<long, int> toNum;

long transform(const unsigned long n)
{
  int arr[10] = {0};
  unsigned long m = n;
  while (m > 0)
  {
    int d = m % 10;
    arr[d]++;
    m /= 10;
  }
  unsigned long k = 0;
  for (int i = 0; i < 10; i++)
  {
    k += arr[i];
    k *= 10;
  }
  return k;
}

int main()
{
  long k, m, n = 0;
  int c = 0;
  while (c < GOAL)
  {
    n++;
    m = n*n*n;
    k = transform(m);
    toCnt[k]++;
    if (toNum[k] == 0)
      toNum[k] = (int)n;
    c = toCnt[k];
  }

  long ans = (long)toNum[k];
  ans = ans*ans*ans;
  cout << ans << endl;

  return 0;
}
