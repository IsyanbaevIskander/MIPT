#include <iostream>
#include <vector>

void FloydWarshall(std::vector<std::vector<int>>& matrix, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        matrix[j][k] = std::min(matrix[j][k], matrix[j][i] + matrix[i][k]);
      }
    }
  }
}

void PrintAnswer(std::vector<std::vector<int>>& matrix, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int x;
      std::cin >> x;
      matrix[i][j] = x;
    }
  }

  FloydWarshall(matrix, n);
  PrintAnswer(matrix, n);

  return 0;
}
