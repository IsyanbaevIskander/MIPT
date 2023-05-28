#include <iostream>
#include <vector>
#include <string>

std::vector<int> ZFunction(std::string& str) {
  std::vector<int> z(str.size(), 0);
  int left = 0;
  int right = 0;
  z[0] = str.size();

  for (int i = 1; i < str.size(); ++i) {

    if (i <= right) {
      z[i] = std::min(z[i - left], right - i);
    }

    while (i + z[i] < str.size() && str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }

    if (right < i + z[i]) {
      right = i + z[i];
      left = i;
    }
  }

  return z;
}

int main() {
  std::string str;
  std::cin >> str;

  for (auto i : ZFunction(str)) {
    std::cout << i << " ";
  }
  return 0;
}
