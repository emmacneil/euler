/**
 * File: Euler.java
 * 
 * The Euler class prompts the user for to input an integer, for which the
 * totient function (phi) will be calculated. The totient function of n
 * counts the totatives of n -- the number of positive integers less than
 * or equal to n that are relatively prime with n.
 *
 * Note that no attempt is made at error handling should the user input
 * anything other than a positive integer.
 *
 * Course: COMP 2631, Winter 2014
 * 
 * @author  Evan MacNeil
 * @version 2014-01-12
 */

public class Euler
{
    /**
     * Calculates the number of totatives of n. That is, the number of positive
     * integers less than or equal to n that are relatively prime with n.
     *
     * @param n the number whose totatives are to be counted. Must be a positive
     *          integer.
     * @return  the total number of totatives of n.
     */
    public static long phi(long n)
    {
        if (n == 1) // Special case: phi(1) = 1.
        {
            return 1;
        }

        long base = 2, exp = 1;
        final long SQRT_N = Math.round(Math.sqrt(n));

        while (base <= SQRT_N)        // Factorize n into prime factors.
        {
            if (n % base == 0)        // If base divides n...
            {
                while (n % base == 0)
                {
                    n   /= base;      // ...divide n by base repeatedly
                    exp *= base;      // record the number of divisions.
                }

                // Take advantage of the fact that phi() is multiplicative.
                // base^exp and n are relatively prime to each other.
                return phiPrimePower(base, exp) * phi(n);
            } // end if

            base++;
        } // end while

        // If we reach here, n is a prime number, and was not modified by the
        // above loop. Special case for a prime number p is phi(p) = p - 1
        return n - 1;
    }



    /**
     * Calculates the number of totatives of some number defined by a base to an
     * exponent. The base must be a prime number, and both the base and
     * exponents must be positive integers. This is an easily calculated special
     * case of the totient function.
     *
     * @param base the base of the integer whose totatives are to be counted.
     * @param long the exponent of the integer whose totatives are to be
     *             counted.
     * @return     the number of totatives of the the integer defined by the
     *             given parameters.
     */
    public static long phiPrimePower(final long base, final long exp)
    {
        return (exp / base) * (base - 1);
    }



    public static void main(String args[])
    {
        double d = 0.0, tmp;
	long n = 0, p;
        
	for (int i = 0; i < 1000000; i++)
        {
	  p = phi(i);
          tmp = (double)i / (double)p;
	  if (tmp > d)
	  {
	    d = tmp;
	    n = i;
	  }
	}

        System.out.println(n);
    }
}
