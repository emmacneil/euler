/* Project Euler - Problem 103
 * Special Subset Sums: Optimum
 *
 * This is a brute force solution. We begin with the set that the described algorithm would have
 * us believe is a "optimum" set,
 * 
 *                                A = { 22, 33, 40, 41, 42, 44, 47 }
 * 
 * We then test all sets whose elements are the same as A's, plus or minus 4. This test is sped up
 * considerably by rejecting sets whose sum is greater than or equal to the sum of A or the sum of
 * any other special set we've discovered.
 *   It also turns out that the elements of the true optimum set are all within 2 of A's, so we
 * could have reduced the range of our search.
 */

#include "next_combination.h"
#include <iostream>
#include <vector>

using namespace std;

const int BASE   = 9;
const int OFFSET = -4;
const bool OUTPUT = true;



void print_subvec(vector<int>::iterator begin, vector<int>::iterator end)
{
  if (begin >= end)
    cout << "[]";
  else if (begin + 1 == end)
    cout << "[" << (*begin) << "]";
  else {
    cout << "[" << (*begin);
    for (vector<int>::iterator it = begin + 1; it != end; it++)
      cout << ", " << (*it);
    cout << "]";
  }
}



void print_vec(vector<int> & v)
{
  if (v.size() == 0)
    cout << "[]";
  else if (v.size() == 1)
    cout << "[" << v[0] << "]";
  else {
    cout << "[" << v[0];
    for (vector<int>::iterator it = v.begin() + 1; it != v.end(); it++)
      cout << ", " << (*it);
    cout << "]";
  }
}



// Returns the sum of the elements of v.
int sum(vector<int> & v)
{
  int ret = 0;
  for (int a : v) ret += a;
  return ret;
}



// This is how we generate all sets with elements within some range of A's.
// Using the BASE and OFFSET constants defined above, we express n in base BASE, add OFFSET to
// each digit, then add the result to elements of A.
//   e.g.: for A = { 22, 33, 40, 41, 42, 44, 47}, BASE = 5, OFFSET = -2, n = 70899,
//
//   Digits of n in base 5 :      4,  2,  3,  2,  0,  4,  4
//   Add OFFSET to each digits :  2,  0,  1,  0, -2,  2,  2
//   Add offset digits to A    : 20, 33, 41, 41, 40, 46, 49
vector<int> add(const vector<int> & v, int n)
{
  vector<int> ret(v);
  int sz = v.size();
  int d;
  for (int i = sz - 1; i >= 0; i--) {
    d = (n % BASE) + OFFSET;
    ret[i] += d;
    n /= BASE;
  }
  return ret;
};



// Returns true is the sum of B is not equal to the sum of C
bool condition1(vector<int> & B, vector<int> & C)
{
  return sum(B) != sum(C);
}



// Returns true is when C has more elements than B, C's sum is larger than B's
bool condition2(vector<int> & B, vector<int> & C)
{
  if (B.size() == C.size())
    return true;
  return (B.size() < C.size()) ? (sum(B) < sum(C)) : (sum(B) > sum(C));
}



bool special(vector<int> & A)
{
  if (!is_sorted(A.begin(), A.end()))
    return false;

  // Generate all disjoint pairs of subsets, B and C.
  size_t sizeA = A.size();
  for (int sizeB = 1; sizeB <= sizeA / 2; sizeB++) {
    // For each subset B of size sizeB...
    do {
      vector<int> B(A.begin(), A.begin() + sizeB);
      for (int sizeC = sizeB; sizeB + sizeC <= sizeA; sizeC++) {
	vector<int> tmp(A.begin() + sizeB, A.end());
	// For each subset A of size sizeA, taken from the elements not chosen in B ...
	do {
	  vector<int> C(tmp.begin(), tmp.begin() + sizeC);
	  // Check if both conditions are satisfied.
	  // If not, reject
	  if ( !condition1(B, C) || !condition2(B, C) )
	    return false;
	} while (next_combination(tmp.begin(), tmp.begin() + sizeC, tmp.end()));
      }
    } while (next_combination(A.begin(), A.begin() + sizeB, A.end()));
  }

  // If all disjoint subset pairs passed the test, accept.
  return true;
}



int main(int argc, char * argv[])
{
  vector<int> A = {22, 33, 40, 41, 42, 44, 47};
  int best_sum = 269, best_i, maxi = 1;

  // Compute the number of sets to test...
  for (int i = 0; i < A.size(); i++)
    maxi *= BASE;
  
  // For each set whose elements are within some range of A's ...
  // (range defined by BASE and OFFSET constants, see comments for add() above)
  for (int i = 0; i < maxi; i++) {
    // Get set with elements in correct range
    vector<int> tmp(add(A, i));

    // If the sum of this set is greater than the best known, try another set.
    if (sum(tmp) > best_sum)
      continue;

    // If the set matches the conditions for specialness
    if (special(tmp)) {
      // Update best known sum
      best_sum = sum(tmp);
      best_i = i;
      if (OUTPUT) {
        print_vec(tmp);
        cout << endl << flush;
      }
    }
  }

  // Print answer
  vector<int> ans(add(A, best_i));
  for (int a : ans)
    cout << a;
  cout << endl;

  return 0;
}
