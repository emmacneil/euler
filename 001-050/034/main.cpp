#include <ctime>
#include <iostream>

using namespace std;

int fact(const int N)
{
  if (N < 1) return 1;
  return N * fact(N-1);
}



int dfact(const int N)
{
  int m = 0, n = N;
  while (n > 0)
  {
    m += fact(n % 10);
    n /= 10;
  }
  return m;
}


int main (int argc, char* argv[])
{
  // Calculate...
  int n, sum = 0;
  for (int i = 10; i < 1000000; i++)
    if (i == dfact(i))
      sum += i;

  cout << sum << endl;  
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
