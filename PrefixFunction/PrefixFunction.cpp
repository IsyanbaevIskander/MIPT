#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunction(std::string& str) {
  std::vector<int> pr(str.size(), 0);

  for (int i = 1; i < int(str.size()); ++i) {
    int k = pr[i - 1];

    while (k > 0 && str[k] != str[i]) {
      k = pr[k - 1];
    }

    if (str[k] == str[i]) {
      pr[i] = k + 1;
    }
  }

  return pr;
}

int main() {
  std::string str;
  std::cin >> str;

  for (auto i : PrefixFunction(str)) {
    std::cout << i << " ";
  }
  return 0;
}
