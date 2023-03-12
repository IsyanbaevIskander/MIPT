#include <iostream>
#include <numeric>
#include <cstring>
#include "rational.h"

void Rational::Reduce() {
  int gcd = std::gcd(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    p_ = -p_;
    q_ = -q_;
  }
}

Rational::Rational(int p, int q) {  // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero();
  }

  p_ = p;
  q_ = q;

  Reduce();
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int a) {
  p_ = a;
  Reduce();
}

void Rational::SetDenominator(int b) {
  if (b == 0) {
    throw RationalDivisionByZero();
  }
  
  q_ = b;
  Reduce();
}

Rational& Rational::operator+=(const Rational& second) {
  p_ = p_ * second.q_ + q_ * second.p_;
  q_ = q_ * second.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator-=(const Rational& second) {
  p_ = p_ * second.q_ - q_ * second.p_;
  q_ = q_ * second.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

Rational& Rational::operator*=(const Rational& second) {
  p_ *= second.p_;
  q_ *= second.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& second) {
  if (second.p_ == 0) {
    throw RationalDivisionByZero();
  }
  
  p_ *= second.q_;
  q_ *= second.p_;
  Reduce();
  return *this;
}

Rational Rational::operator+() const {
  Rational copy = *this;
  return copy;
}

Rational Rational::operator-() const {
  Rational copy = *this;
  copy.p_ = -copy.p_;
  return copy;
}

Rational operator+(const Rational& first, const Rational& second) {
  Rational copy = first;
  copy += second;
  return copy;
}

Rational operator-(const Rational& first, const Rational& second) {
  Rational copy = first;
  copy -= second;
  return copy;
}

Rational operator*(const Rational& first, const Rational& second) {
  Rational copy = first;
  copy *= second;
  return copy;
}

Rational operator/(const Rational& first, const Rational& second) {
  if (second.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }
  
  Rational copy = first;
  copy /= second;
  return copy;
}

std::ostream& operator<<(std::ostream& out, const Rational& first) {
  int q = first.GetDenominator();
  
  if (q == 1) {
    out << first.GetNumerator();
    return out;
  }
  
  out << first.GetNumerator() << "/" << first.GetDenominator();
  return out;
}

std::istream& operator>>(std::istream& in, Rational& first) {
  char s[100];
  bool is_positive = true;
  bool is_end = false;
  in >> s;
  int length = strlen(s);
  int p = 0, q = 0;
  int index = 0;

  while (s[index] != '/') {

    if (s[index] == '-') {
      is_positive = !is_positive;
    } else if (s[index] == '+') {
      ++index;
      continue;
    } else {
      p = p * 10 + s[index] - '0';
    }
    
    ++index;
    if (index == length) {
      is_end = !is_end;
      break;
    }
  }

  if (is_end) {
    q = 1;
  } else {
    ++index;
    
    while (index != length) {
      
      if (s[index] == '-') {
        is_positive = !is_positive;
      } else if (s[index] == '+') {
        ++index;
        continue;
      } else {
        q = q * 10 + s[index] - '0';
      }
      
      ++index;
    }
  }

  if (!is_positive) {
    p = -p;
  }
  first.SetDenominator(1);
  first.SetNumerator(p);
  first.SetDenominator(q);
  return in;
}

bool operator==(const Rational& first, const Rational& second) {
  return (first.GetNumerator() == second.GetNumerator() && first.GetDenominator() == second.GetDenominator());
}

bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}

bool operator<(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator();
}

bool operator<=(const Rational& first, const Rational& second) {
  return (first < second || first == second);
}

bool operator>(const Rational& first, const Rational& second) {
  return !(first <= second);
}

bool operator>=(const Rational& first, const Rational& second) {
  return !(first < second);
}
