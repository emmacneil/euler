/**
 * Project Euler - Problem 206
 * Concealed Square
 *
 * The smallest candidate for a number of the form 1_2_3_4_5_6_7_8_9_0 is the
 * square root of 1020304050607080900, which is approximately equal to
 * 1010101010. The largest candidate is the square root of 1929394959697989990,
 * which is approximately equal to 1389026623. We can simply try squaring each
 * of the integers between these roots. Moreover, it can be seen that the
 * correct solution must end in a zero, so we can increment in tens.
 */
#include <iostream>

using namespace std;

bool solve(unsigned long m)
{
  unsigned long n = m * m;
  if (n / 1000000000000000000UL == 1)
  {
    n -= (n / 100000000000000000UL) * 100000000000000000UL;
    if (n / 10000000000000000UL == 2)
    {
      n -= (n / 1000000000000000UL) * 1000000000000000UL;
      if (n / 100000000000000UL == 3)
      {
        n -= (n / 10000000000000UL) * 10000000000000UL;
        if (n / 1000000000000UL == 4)
        {
          n -= (n / 100000000000UL) * 100000000000UL;
          if (n / 10000000000UL == 5)
          {
            n -= (n / 1000000000UL) * 1000000000UL;
            if (n / 100000000UL == 6)
            {
              n -= (n / 10000000UL) * 10000000UL;
              if (n / 1000000UL == 7)
              {
                n -= (n / 100000UL) * 100000UL;
                if (n / 10000UL == 8)
                {
                  n -= (n / 1000UL) * 1000UL;
                  if (n / 100UL == 9)
                  {
                    n -= (n / 10UL) * 10UL;
		    if (n == 0)
		      return true;
		  }
		}
              }
            }
	  }
	}
      }
    }
  }

  return false;
}

// 1020304050607080900

int main(int argc, char * argv[])
{
  unsigned long start = 1010101010L;
  unsigned long end = 1389026623L;
  unsigned long inc = 10;
  for (unsigned long m = start; m < end; m += inc)
  {
    if (solve(m))
    {
      cout << m << endl;
      break;
    }
  }
  return 0;
}
