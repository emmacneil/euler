/**
 * Project Euler - Problem 80
 * Square Root Digital Expansion
 *
 * Just a simple computation. The square root of each integer from 1 to 100
 * (excluding rational square roots) is calculated to 200-digit precision using
 * the Babylonian method. To compute the square root of S, we take x0 = 0,
 * x1 = sqrt(S) and then
 *
 *                       x_(n+1) = 1/2 (x_n + S/x_n)
 *
 * We continue this process until the series converges with a difference less
 * than 1e-195.
 */

import java.math.BigDecimal;
import java.math.MathContext;

public class Euler
{
  private static final MathContext mc = new MathContext(200);
  private static final BigDecimal eps = (new BigDecimal("0.1")).pow(195, mc);
  private static final BigDecimal half = new BigDecimal("0.5", mc);
  
  // Compute the square root of s to 200 digits of precision using the
  // Babylonian method.
  public static BigDecimal bdSqrt(int s)
  {
    BigDecimal S = new BigDecimal(s, mc);
    BigDecimal a = new BigDecimal("0", mc);
    BigDecimal b = new BigDecimal(Math.sqrt(s), mc);

    BigDecimal diff = b.subtract(a, mc);
    while (diff.abs().compareTo(eps) > 0)
    {
      a = b;
      b = S.divide(a, mc);
      b = b.add(a, mc);
      b = b.multiply(half, mc);
      diff = b.subtract(a, mc);
    }

    return b;
  }

  // Add up the first 100 digits (before or after the decimal point) of bd.
  public static int digitSum(BigDecimal bd)
  {
    String str = bd.toPlainString();
    int n = 0;
    for (int i = 0; i < 101; i++)
      n += str.charAt(i) == '.' ? 0 : str.charAt(i) - '0';
    return n;
  }

  public static void main(String args[])
  {
    BigDecimal bd;
    int j = 2, n = 0;

    for (int i = 2; i < 100; i++)
    {
      if (i == j * j) // Skip square numbers
      {
        j++;
        continue;
      }
      bd = bdSqrt(i);
      n += digitSum(bd);
    }
    
    System.out.println(n);
  }
}
