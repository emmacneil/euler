/* Project Euler - Problem 105
 * Special Subset Sums: Testing
 *
 * ...
 */

#include "next_combination.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

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
  sort(A.begin(), A.end());

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



// Takes a line of text consisting of numbers separated by single spaces ' ' and returns a
// vector containing those numbers.
// All characters in str should be decimal digits, spaces ' ', or null characters \0.
vector<int> str_to_vec(char str[256])
{
  int i, j;
  vector<int> ret;

  // Set i to point to beginning of next number,
  // and j to point to end of next number.
  // Parse number
  // If j points to a null character, end.
  
  i = j = 0;
  while (str[j] != '\0') {
    i = j++;
    while ( (str[j] != ' ') && (str[j] != '\0') )
      j++;
    ret.push_back(atoi(str + i));
  }
  return ret;
}



int main(int argc, char * argv[])
{
  vector<int> A = {1211,1212,1287,605,1208,1189,1060,1216,1243,1200,908,1210};
  int ans = 0;
  char str[256];

  while (cin.getline(str, 256)) {
    vector<int> A = str_to_vec(str);

    if (special(A)) {
      ans += sum(A);
      if (OUTPUT) {
	print_vec(A);
	cout << endl;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
