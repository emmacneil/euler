/* output.hpp
 *
 * Utility functions for nicely outputting frequently-used objects.
 */



#include <iostream>
#include <vector>



// Overload the << operator for vectors. Example:
//   vector<string> v = {"hello", "world"}
//   cout << v << endl;                    // output: {hello, world}
template <class T>
std::ostream & operator << (std::ostream & os, const std::vector<T> v)
{
  os << "{";
  if (v.size() > 0)
    os << v[0];
  for (int i = 1; i < v.size(); i++)
    os << ", " << v[i];
  os << "}";
  return os;
}

