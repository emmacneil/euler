/**
 * partition
 *
 * Prints all possible partitions of the integer n into k parts. If k is not
 * specified, or if k = 0, then all partitions of n are printed regardless of
 * the numbers of parts.
 *
 * Usage:
 * 
 *     partition n [k]
 *
 * n, the integer to partition.
 * k, the number of sets into which to partition n, optional.
 */

#include <cstdlib>
#include <iostream>

using namespace std;



bool output = true;

int part(int *p);
int partk(int *p, int n);
void print_partition(int *p);



int main(int argc, char *argv[])
{
  int n = 0, k = 0, *p;

  // Handle arguments
  if (argc == 1)
  {
    cout << "Not enough arguments specified. Exiting." << endl;
    return 1;
  }
  
  for (int arg = 1; arg < argc; arg++)
  {
    if (argv[arg][0] == '-')
    {
      if (argv[arg][1] == 'o')
        output = true;
    }
    else if (n == 0)
      n = atoi(argv[arg]);
    else if (k == 0)
      k = atoi(argv[arg]);
    else
    {
      cout << "Too many arguments specified. Exiting." << endl;
      return 1;
    }
  }

  if (n == 0)
  {
    cout << "0 partitions total." << endl;
    return 0;
  }

  if (n < 0 || k < 0)
  {
    cout << "Values cannot be negative. Exiting" << endl;
    return 1;
  }

  // Now do real work...
  // If k was specified
  if (k)
  {
    // Allocate array
    p = new int[k + 1];
  
    p[0] = n - k + 1;
    for (int i = 1; i < k; i++)
      p[i] = 1;
    p[k] = 0;
    cout << partk(p, n) << " partitions total." << endl;
  }
  else
  {
    // Allocate array
    p = new int[n + 1];
  
    p[0] = n;
    for (int i = 1; i <= n; i++)
      p[i] = 0;
    cout << part(p) << " partitions total." << endl;
  }

  // Delete array
  if (p != 0)
    delete p;
  return 0;
}



int part(int *p)
{
  int a, i = 0, j, r = 0;

  // Output
  if (output)
    print_partition(p);

  // Basis case, array = [1, 1, ..., 1]
  if (p[0] == 1)
    return 1;

  // Find last element of array larger than 1
  while (p[i+1] > 1)
    i++;

  // Find sum of sub-array beginning at that element
  j = i;
  while (p[j] != 0)
    r += p[j++];

  a = p[i] - 1;
  while (r >= a)
  {
    p[i++] = a;
    r -= a;
  }
  p[i] = r;
  if (r > 0)
    p[i+1] = 0;

  return 1 + part(p);
}



int partk(int *p, int n)
{
  int a, i, m = 0;

  if (output)
    print_partition(p);

  // Find first element smaller than p[0] - 1
  while ( (p[i] >= p[0] - 1) && (p[i] > 0) )
    i++;

  if (p[i] == 0)
    return 1;

  a = p[i] + 1;
  for (int j = 1; j <= i; j++)
    p[j] = a;

  for (int j = 1; p[j] > 0; j++)
    m += p[j];
  p[0] = n - m;

  return 1 + partk(p, n);
}



void print_partition(int *p)
{
  int i = 1;
  
  cout << "[" << p[0];
  
  while (p[i] != 0)
    cout << ", " << p[i++];
  
  cout << "]" << endl;
}
