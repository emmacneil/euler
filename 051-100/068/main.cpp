// Problem 68 - Magic 5-gon Ring

#include <iostream>

using namespace std;

const int n_nums = 10;
const int arr_len = 15;
const long max_str = 9999999999999999L;
const bool OUTPUT = false;

int arr[arr_len];
int available[n_nums];
int sum;
long maximum = 0;

void print_arr()
{
  cout << arr[0];
  for (int i = 1; i < arr_len; i++)
  {
    if (i % 3 == 0)
      cout << "; ";
    else
      cout << ",";
    cout << arr[i];
  }
  cout << endl;
}

long concat(long a, long b)
{
  long n = b;
  while (n > 0)
  {
    a *= 10;
    n /= 10;
  }
  return a + b;
}

long getstr()
{
  if (OUTPUT)
    print_arr();

  int k, n = n_nums + 1;
  long l = 0;
  for (int i = 0; i < arr_len; i += 3)
  {
    if (arr[i] < n)
    {
      n = arr[i];
      k = i;
    }
  }

  for (int i = 0; i < arr_len; i++)
  {
    l = concat(l, arr[k]);
    k = (k+1) % arr_len;
  }

  if (l > max_str)
    l = 0;
  
  return l;
}

void solve(int k)
{
  if (k > 0 && k % 3 == 0)
    if (arr[k-1] + arr[k-2] + arr[k-3] != sum)
      return;

  if (k >= arr_len)
  {
    long l = getstr();
    maximum = l > maximum ? l : maximum;
    return;
  }

  if (arr[k] != 0)
  {
    solve(k + 1);
    return;
  }

  for (int i = 0; i < n_nums; i++)
  {
    if (available[i])
    {
      available[i] = false;
      arr[k] = i + 1;
      if (k % 3 == 2)
        arr[ (k + 2) % arr_len ] = i + 1;
      if (k % 3 == 1)
        arr[ (k + (arr_len - 2)) % arr_len ] = i + 1;
      
      if (k == 2)
        sum = arr[0] + arr[1] + arr[2];
      
      solve(k + 1);
      available[i] = true;
    }
  }
  arr[k] = 0;
  if (k % 3 == 2)
    arr[ (k + 2) % arr_len ] = 0;
  if (k % 3 == 1)
    arr[ (k + (arr_len - 2)) % arr_len ] = 0;
}

int main()
{
  // Initialize arrays
  for (int i = 0; i < arr_len; i++)
    arr[i] = 0;
  for (int i = 0; i < n_nums; i++)
    available[i] = true;

  sum = 0;

  solve(0);

  // Output
  cout << maximum << endl;

  return 0;
}
