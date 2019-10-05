/* Project Euler - Problem 105
 * Special Subset Sums: Testing
 *
 * Let B and C be subsets of A of equal size, |B| = |C|. Let the elements of B and C be
 * 
 *                                     B = {b_1, b_2, ..., b_n}
 *                                     C = {c_1, c_2, ..., c_n}
 * 
 * If b_i < c_i for all i = 1, 2, ..., n, then this pair does not need to be tested.
 *   The solution is to generate all disjoint subset pairs of equal size, and count the number of
 * them for which b_i > c_i for some i.
 */

#include "next_combination.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int BOUND = 12;
const bool OUTPUT = false;



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


bool test(vector<int> & B, vector<int> & C)
{
  for (int i = 0; i < B.size(); i++) {
    if (B[i] > C[i]) return true;
  }
  return false;
}



int count(vector<int> & A)
{
  int ret = 0;

  // Generate all disjoint pairs of subsets, B and C of equal size
  size_t sizeA = A.size();
  for (int size = 1; size <= sizeA / 2; size++) {
    // For each subset B ...
    do {
      vector<int> B(A.begin(), A.begin() + size);
      vector<int> tmp(A.begin() + size, A.end());
      // And each subset C, taken from the elements C-B ...
      do {
	vector<int> C(tmp.begin(), tmp.begin() + size);
	
	if (B[0] > C[0]) // Avoid double counting subset pairs
	  continue;      // By requiring the minimum element of C is greater than that of B
	
	// If this pair needs to be tested ...
	if (test(B, C)) {
	  if (OUTPUT) {
	    print_vec(B); cout << " "; print_vec(C); cout << endl;
	  }
	  // ... increment the counter
	  ret++;
	}
      } while (next_combination(tmp.begin(), tmp.begin() + size, tmp.end()));

    } while (next_combination(A.begin(), A.begin() + size, A.end()));
  }

  return ret;
}



int main(int argc, char * argv[])
{
  vector<int> A;
  for (int i = 1; i <= BOUND; i++)
    A.push_back(i);

  cout << count(A) << endl;

  return 0;
}
