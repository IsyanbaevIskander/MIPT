#ifndef RATIONAL_H
#define RATIONAL_H


#include <iostream>
#include <numeric>
using namespace std;

class RationalDivisionByZero: public std::exception {
};

class Rational {
private:
  int p = 1;
  int q = 1;

  void Reduce() {
    int gcd = std::gcd(p, q);
    p /= gcd;
    q /= gcd;
  }

public:
  Rational(int p = 0, int q = 1) {
    this->p = p;
    this->q = q;

    if (q == 0) {
      throw RationalDivisionByZero();
    }

    Reduce();

    if (q < 0) {
      this->p = -p;
      this->q = -q;
    }
  }

  Rational(const Rational& r) {
    p = r.p;
    q = r.q;
  }

  Rational& operator+=(const Rational& other) {
    p = p * other.q + q * other.p;
    q = q * other.q;
    Reduce();
    return *this;
  }

  Rational& operator++() {
    *this += 1;
    return *this;
  }

  Rational operator++(int) {
    Rational copy = *this;
    ++*this;
    return copy;
  }

  Rational& operator-=(const Rational& other) {
    p = p * other.q - q * other.p;
    q = q * other.q;
    Reduce();
    return *this;
  }

  Rational& operator--() {
    *this -= 1;
    return  *this;
  }

  Rational operator--(int) {
    Rational copy = *this;
    --*this;
    return copy;
  }

  Rational& operator*=(const Rational& other) {
    p = p * other.p;
    q = q * other.q;
    Reduce();
    return *this;
  }

  Rational& operator/=(const Rational& other) {
    p = p / other.q;
    q = q * other.p;
    Reduce();
    return *this;
  }

  Rational& operator=(const Rational& other) {
    p = other.p;
    q = other.q;
    return *this;
  }

  int GetNumerator() const {
    return this->p;
  }

  int GetDenominator() const {
    return this->q;
  }

  void SetNumerator(int a) {
    p = a;
    Reduce();
  }

  void SetDenominator(int b) {
    if (b == 0) {
      throw RationalDivisionByZero();
    }
    q = b;
    Reduce();
  }

  Rational& operator+() {
    SetNumerator(p);
    return *this;

  }

  Rational& operator-() {
    SetNumerator(-p);
    return *this;
  }
};

Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}

Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}

Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}

Rational operator/(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy /= other;
  return copy;
}

ostream& operator<<(ostream& out, const Rational& first) {
  int q = first.GetDenominator();
  if (q == 1) {
    return out << first.GetNumerator();
  }
  return out << first.GetNumerator() << "/" << first.GetDenominator();
}

void operator>>(istream& in, Rational& first) {
  int a, b;
  char str;
  in >> a;
  in >> str;
  in >> b;
  if (b < 0) {
    a = -a;
    b = -b;
  }
  first.SetNumerator(a);
  first.SetDenominator(b);
}

bool operator<(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator();
}

bool operator>(const Rational& first, const Rational& second) {
  return second < first;
}

bool operator==(const Rational& first, const Rational& second) {
  return !(first < second || second < first);
}

#endif