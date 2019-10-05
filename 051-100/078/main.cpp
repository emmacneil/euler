#include <iostream>
#include <cstdlib>

using namespace std;

const bool OUTPUT = false;

long *pents;

long partitions(long n)
{
  long *arr = new long[n];
  arr[0] = 1;
  
  long i = 1;
  for ( ; i < n; i++)
  {
    arr[i] = 0;
    long* k = pents;
    while (i - (*k) >= 0)
    {
      switch ( (k-pents) % 4)
      {
      case 1:
      case 2:
        arr[i] += arr[i - *k++];
	arr[i] %= 1000000;
      break;
      default:
        arr[i] -= arr[i - *k++];
	arr[i] %= 1000000;
	if (arr[i] < 0)
	  arr[i] += 1000000;
      }
    }
    if (OUTPUT)
      cout << i << " = " << arr[i] << endl;
    if (arr[i] % 1000000 == 0)
      break;
  }

  delete[] arr;
  return i;
}

long pent(long n)
{
  return (3*n*n-n)/2;
}

void gen_pents(int n)
{
  pents = new long[n];

  pents[0] = 0;
  for (int i = 1; i < n; i++)
  {
    int m = i % 2 == 0 ? -(i/2) : (i+1)/2 ;
    pents[i] = pent(m);
  }
}

int main(int argc, char *argv[])
{
  int n = 100000;
  if (argc == 2)
    n = atoi(argv[1]);

  gen_pents(10000);

  cout << partitions(n) << endl;

  delete[] pents;
}
