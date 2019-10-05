/*
 * Project Euler - Problem 88
 * Product-Sum Numbers
 *
 * The idea here was to build up stacks of integers greater than 1
 *
 *     2
 *     2 2
 *     2 2 2
 *     2 2 2 2 ...
 *
 * In which no number on the stacks exceeds a number below it. We build stacks
 * in which all numbers are at most 2, then stacks in which they are at most
 * 3, etc. From each stack, we can add a bunch of 1's until the sum of the
 * terms matches their product. k is then the size of the stack, and k's
 * product-sum number N is the product of all the integers on the stack.
 *   Even easier, though, than adding 1's to the stack to find k is to use a
 * formula. Let p be the product of the numbers on the stack, let s be their
 * sum, and let d be the number of integers on the stack. Then
 *
 *                               k = p - s + d
 *
 * Then we store the product p as the k'th element in an array if it is smaller
 * than any number which has already been stored there.
 */

#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

const bool OUTPUT = false;
const int  BOUND  = 12000;

set<int> nums;
int arr[BOUND+1];



void solve(const int prod, const int sum, const int prev, const int depth)
{
  const int k = prod - sum + depth;
  
  if (k > BOUND)
    return;
  
  // Store the product-sum in arr[k]
  if (k > 1)
    arr[k] = prod < arr[k] ? prod : arr[k];

  // Add a number to the stack
  for (int i = 2; i <= prev; i++)
    solve(prod * i, sum + i, i, depth + 1);
}



int main()
{
  int n = 0;

  // Initialize array
  for (int i = 2; i <= BOUND; i++)
    arr[i] = 0x7fffffff;

  // Solve
  for (int i = 2; i <= BOUND; i++)
    solve(i, i, i, 1); // ???

  // Add numbers from array to set
  for (int i = 2; i <= BOUND; i++)
  {
    if (OUTPUT) printf("k = %5d, N = %5d\n", i, arr[i]);
    nums.insert(arr[i]);
  }

  // Get the sum of all the numbers in the set.
  set<int>::iterator it;
  for (it = nums.begin(); it != nums.end(); it++)
    n += *it;

  // Output solution
  cout << n << endl;

  return 0;
}
