#include <cmath>
#include <iostream>
#include <utility>

#define N_PAIRS 1000

using namespace std;

int main()
{
  pair<int, int> pairs[N_PAIRS];

  for (int i = 0; i < N_PAIRS; i++)
    cin >> pairs[i].first >> pairs[i].second;

  int max_ind = -1;
  double max_val = 0.0, val;
  for (int i = 0; i < N_PAIRS; i++)
  {
    val = pairs[i].second * log(pairs[i].first);
    if (val > max_val)
    {
      max_val = val;
      max_ind = i;
    }
  }

  cout << max_ind + 1 << endl;

  return 0;
}
