
#include "rational.h"

int128_t gcd(int128_t a, int128_t b)
{
  if (b < 0) return gcd(a, -b);
  if (a < 0) return gcd(-a, b);
  if (b > a) return gcd(b, a);
  if (b == 0) return a;
  return gcd(b, a % b);
}

rational& rational::operator = (const rational& q)
{
  numer = q.numer;
  denom = q.denom;
  return *this;
}

rational& rational::operator = (const int128_t& n)
{
  numer = n;
  denom = 1;
  return *this;
}

rational rational::operator - ()
{
  rational tmp(-this->numer, this->denom);
  return tmp;
}

rational rational::operator + (const rational& q)
{
  int128_t d, n;
  
  d = this->denom * q.denom;
  n = this->numer * q.denom + this->denom * q.numer;
  
  rational tmp(n, d);
  
  return tmp;
}

rational rational::operator - (const rational& q)
{
  int128_t d, n;
  
  d = this->denom * q.denom;
  n = this->numer * q.denom - this->denom * q.numer;
  
  rational tmp(n, d);
  
  return tmp;
}

rational rational::operator * (const rational& q)
{
  rational tmp(this->numer * q.numer, this->denom * q.denom);
  return tmp;
}

rational rational::operator / (const rational& q)
{
  rational tmp(this->numer * q.denom, this->denom * q.numer);
  return tmp;
}
  
rational& rational::operator += (const rational& q)
{
  *this = *this + q;
  return *this;
}

rational& rational::operator -= (const rational& q)
{
  *this = *this - q;
  return *this;
}

rational& rational::operator *= (const rational& q)
{
  *this = *this * q;
  return *this;
}

rational& rational::operator /= (const rational& q)
{
  *this = *this / q;
  return *this;
}
  
bool rational::operator == (const rational& q)
{
  return (this->numer == q.numer) && (this->denom == q.denom);
}

bool rational::operator != (const rational& q)
{
  return (this->numer != q.numer) || (this->denom != q.denom);
}

bool rational::operator < (const rational& q)
{
  return this->numer * q.denom < q.numer * this->denom;
}

bool rational::operator <= (const rational& q)
{
  return ((*this == q) || (*this < q));
}

bool rational::operator > (const rational& q)
{
  return this->numer * q.denom > q.numer * this->denom;
}

bool rational::operator >= (const rational& q)
{
  return ((*this == q) || (*this > q));
}

rational::operator int128_t ()
{
  return numer / denom;
}

std::ostream& operator << (std::ostream& out, const rational& q)
{
  out << q.numer << '/' << q.denom;
  return out;
}

void rational::reduce()
{
  int128_t d = gcd(numer, denom);
  numer /= d;
  denom /= d;
  denom = numer == 0 ? 1 : denom;
  if (denom < 0)
  {
    numer = -numer;
    denom = -denom;
  }
}
