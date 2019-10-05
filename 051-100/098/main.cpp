/*
 * Project Euler - Problem 98
 * Anagramic Squares
 *
 * First we construct a graph in which all the nodes are the words contained in
 * the data file words.txt. Then, for every pair of words that form an 
 * anagramic pair, we make an edge between their nodes. Then we iterate through 
 * each edge and check if the words form a square-anagramic pair. This is done 
 * by a rather expensive computation in which we try all possible mappings of 
 * digits to characters.
 *
 *             ANAGRAM   ANAGRAM   ANAGRAM   ANAGRAM   ANAGRAM
 *             123456789 123456798 123456879 123456897 123456978 ...
 *
 * If the same letter would get mapped to two different numbers, we map it only
 * to the last number, so that the above mappings would result in the following
 * transformations:
 *
 *             6264567   6264567   6264568   6264568   6264569   ...
 */

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const bool OUTPUT = true;

int digits[9] = {1,2,3,4,5,6,7,8,9};

struct node
{
  string str;
};

struct graph
{
  int n, m;
  vector<node*> nodes;
  vector< pair<node*,node*> > edges;
  graph() : n(0), m(0) {}
};



// Returns < 0 if a < b
//         > 0 if a > b
//           0 if a = b
int charcmp(const void *a, const void *b)
{
  return *(char *)a - *(char *)b;
}



// Returns true if str1 and str2 are anagrams
bool anagram(string str1, string str2)
{
  char *c_str1, *c_str2;
  bool b = true;
  
  if (str1.size() != str2.size())
    return false;

  c_str1 = new char[str1.size() + 1];
  c_str2 = new char[str2.size() + 1];
  strcpy(c_str1, str1.c_str());
  strcpy(c_str2, str2.c_str());

  qsort(c_str1, str1.size(), sizeof(char), charcmp);
  qsort(c_str2, str2.size(), sizeof(char), charcmp);
  
  for (int i = 0; i < str1.size(); i++)
    if (c_str1[i] != c_str2[i])
      b = false;

  delete[] c_str1;
  delete[] c_str2;

  return b;
}



// Returns true if n is a square number
bool is_sq(int n)
{
  int a = (int)( 0.5 + sqrt(n) );
  return a * a == n;
}



// Returns 0 if str1 and str2 do not form a square-anagram pair
// Otherwise, returns the largest square number formed by str1 or str2
int square_anagram(string str1, string str2)
{
  int a, b, m = 0, len = str1.size();
  map<char,int> mapping;
  
  do
  {
    for (int i = 0; i < len; i++)
      mapping[str1[i]] = digits[i];

    a = 0; b = 0;
    for (int i = 0; i < len; i++)
    {
      a *= 10; b *= 10;
      a += mapping[str1[i]];
      b += mapping[str2[i]];
    }
    if (is_sq(a) && is_sq(b))
    {
      //cout << a << " " << b << endl;
      m = a > m ? a : m;
      m = b > m ? b : m;
    }
  } while (next_permutation(digits, digits+9));
  
  return m;
}



int main()
{
  string str;
  graph g;
  int n, m = 0;

  // Read in words
  while (cin >> str)
  {
    node *n = new node;
    n->str = str;
    g.nodes.push_back(n);
  }
  g.n = g.nodes.size();

  // For each pair of words, check if they are anagramic.
  // If so, add an edge
  for (int i = 0; i < g.n; i++)
    for (int j = i + 1; j < g.n; j++)
      if (anagram(g.nodes[i]->str, g.nodes[j]->str))
        g.edges.push_back(make_pair(g.nodes[i], g.nodes[j]));
  g.m = g.edges.size();

  if (OUTPUT)
    cout << "Graph contains "
         << g.n << " nodes and "
	 << g.m << " edges." << endl;

  for (int i = 0; i < g.m; i++)
  {
    if (m = square_anagram(g.edges[i].first->str, g.edges[i].second->str))
    {
      n = m > n ? m : n;
      if (OUTPUT)
        cout << g.edges[i].first->str << ", " << g.edges[i].second->str << endl;
    }
  }

  cout << n << endl;

  // Clean up
  for (int i = 0; i < g.n; i++)
    delete g.nodes[i];

  return 0;
}
