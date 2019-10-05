#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <ostream>
#include </usr/include/boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::int128_t;

class rational
{
public:
  rational() : numer(0), denom(1) {}
  rational(int128_t n, int128_t d) : numer(n), denom(d) { reduce(); }

  rational& operator = (const rational&);
  rational& operator = (const int128_t&);

  rational operator - ();
  
  rational operator + (const rational&);
  rational operator - (const rational&);
  rational operator * (const rational&);
  rational operator / (const rational&);
  
  rational& operator += (const rational&);
  rational& operator -= (const rational&);
  rational& operator *= (const rational&);
  rational& operator /= (const rational&);
  
  bool operator == (const rational&);
  bool operator != (const rational&);
  bool operator <  (const rational&);
  bool operator <= (const rational&);
  bool operator >  (const rational&);
  bool operator >= (const rational&);

  operator int128_t ();

  friend std::ostream& operator << (std::ostream&, const rational&);

private:
  int128_t numer, denom;

  void reduce();
};

#endif
