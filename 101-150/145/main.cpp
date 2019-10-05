/* Project Euler - Problem 145
 * How Many Reversible Numbers Are There Below One-billion?
 *
 * The computation is straightforward: for each n, we compute the sum of n and its reverse and
 * check if the digits of this sum are odd. This is all done using the obvious approach. The
 * computation is significantly sped up by recognizing that there are no reversible numbers
 * between 100,000,000 and 999,999,999.
 *   
 *   Proof:
 *   Let n be between 100,000,000 and 999,999,999. Let its digits be d9, d8, ..., d1, where d9 is
 * the most significant digit. Let the digits of the sum of n and its reverse be D10, D9, ..., D1.
 * So
 * 
 *                                        d9 d8 d7 d6 d5 d4 d3 d2 d1
 *                                  +     d1 d2 d3 d4 d5 d6 d7 d8 d9
 *                                  = D10 D9 D8 D7 D6 D5 D4 D3 D2 D1
 *
 * D10 may be 0 or 1.
 *   We make a few observations. d5 + d5 is even, so for D5 to be odd, we require d4 + d6 >= 10. For
 * D1 to be odd, we also require d1 + d9 to be odd, which then requires d8 + d2 < 10, otherwise D9
 * is even.
 *   Now suppose d1 + d9 < 10. Then there is no carry over into D2, and since d2 + d8 < 10, there
 * is no carry into D3. So d3 + d7 must be odd for D3 to be odd. But then D7 becomes even, since
 * there is a carry over from d6 + d4.
 *   Suppose instead d1 + d9 >= 10. Then d2 + d8 must be even, but there is still no carry into D3
 * and D7 is still even.
 *   
 *   In a similar manner, it can be shown that tehre are no reversible numbers between 10,000 and
 * 99,999. */



#include <iostream>

using namespace std;



const bool OUTPUT = false;
const unsigned int BOUND = 100000000;


// Return true if all digits of n are odd
bool odd(unsigned int n)
{
  if (n == 0)
    return false;
  
  while (n > 0) {
    if ((n & 1) == 0)
      return false;
    n /= 10;
  }
  
  return true;
}



unsigned int reverse(unsigned int n)
{
  unsigned int ret = 0;

  while (n > 0) {
    ret *= 10;
    ret += (n % 10);
    n /= 10;
  }
  
  return ret;
}



bool reversible(unsigned int n)
{
  if (n % 10 == 0)
    return false;
  return odd(n + reverse(n));
}



int main(int argc, char * argv[])
{
  int k = 0;

  for (int i = 0; i < BOUND; i++) {
    // There are no reversibles between 10,000 and 99,999
    if ( (i >= 10000) && (i <= 99999) ) {
      i = 99999;
      continue;
    }
    if (reversible(i)) {
      if (OUTPUT)
        cout << i << " + " << reverse(i) << " = " << (i + reverse(i)) << endl;
      k++;
    }
  }

  cout << k << endl;

  return 0;
}
