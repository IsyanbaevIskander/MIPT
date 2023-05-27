#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

enum Colour { WHITE, GREY, BLACK };

class Graph {
private:
    std::vector<std::unordered_set<int>> vertexes_;
    std::vector<int> distance_;
    std::vector<int> parents_;
    std::stack<int> stack_;

    bool hascircle_ = false;
    int first_elem_ = -1;
    bool is_ready_ = false;

    void DFS(int vertex, std::vector<Colour>& visited) {
      visited[vertex] = GREY;

      for (auto neighbour : vertexes_[vertex]) {
        if (visited[neighbour] == GREY) {

          if (!is_ready_ && !hascircle_) {
            first_elem_ = neighbour;
            stack_.push(vertex);
          }

          hascircle_ = true;
        }

        if (visited[neighbour] == WHITE) {
          DFS(neighbour, visited);
        }

        if (hascircle_ && !is_ready_ && neighbour == stack_.top()) {
          stack_.push(vertex);

          if (vertex == first_elem_) {
            is_ready_ = true;
          }
        }
      }

      visited[vertex] = BLACK;
    }

public:
    explicit Graph(int n) {
      vertexes_ = std::vector<std::unordered_set<int>>(n);
      distance_ = std::vector<int>(n, 100000000);
      parents_ = std::vector<int>(n, -1);
    }

    friend std::istream& operator>>(std::istream& is, Graph& g);

    bool HasCircle() {
      std::vector<Colour> visited = std::vector<Colour>(vertexes_.size(), WHITE);

      for (int i = 0; i < vertexes_.size(); ++i) {
        DFS(i, visited);
      }

      return hascircle_;
    }

    void CircleBuild() {
      while (!stack_.empty()) {
        std::cout << stack_.top() + 1 << "\n";
        stack_.pop();
      }
    }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);
  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> graph;
  }

  if (graph.HasCircle()) {
    std::cout << "YES\n";
    graph.CircleBuild();
  } else {
    std::cout << "NO";
  }
  return 0;
}
