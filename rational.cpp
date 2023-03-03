#include <iostream>
#include <numeric>
#include "rational.h"
using namespace std;


int main() {
  Rational x = 5;
  cout << x << "\n";
  x.SetDenominator(15);
  cout << x << "\n";
  cin >> x;
  cout << x << "\n";
  return 0;
}