#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int ctoi(const char c)
{
  if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
  if (c >= 'a' && c <= 'z') return c - 'a' + 1;
  return -1;
}

int t(const int n)
{
  if (n < 0) return -1;
  return n * (n + 1) / 2;
}

bool ist(const int n)
{
  for (int i = sqrt(n); i*i+i <= 2*n; i++)
    if (i*i+i == 2*n)
      return true;
  return false;
}

bool iststr(string s)
{
  int sz = s.size();
  int n = 0;
  for (int i = 0; i < sz; i++)
    n += ctoi(s[i]);
  return ist(n);
}

int main (int argc, char* argv[])
{
  // Calculate...
  int n = 0;
  string str;
  while (cin >> str)
    if (iststr(str))
      n++;
  
  cout << n << endl;

  return 0;
}
