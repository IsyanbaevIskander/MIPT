#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>

class Graph {
private:
    std::vector<std::unordered_set<int>> vertexes_;
    std::vector<int> distance_;
    std::vector<int> parents_;

public:
    explicit Graph(int n) {
      vertexes_ = std::vector<std::unordered_set<int>>(n);
      distance_ = std::vector<int>(n, 100000000);
      parents_ = std::vector<int>(n, -1);
    }

    void BFS(int start) {
      --start;
      std::queue<int> queue;
      queue.push(start);
      distance_[start] = 0;

      while (!queue.empty()) {
        int curr = queue.front();
        queue.pop();

        for (auto neighbour : vertexes_[curr]) {
          if (distance_[neighbour] > distance_[curr] + 1) {
            distance_[neighbour] = distance_[curr] + 1;
            parents_[neighbour] = curr;
            queue.push(neighbour);
          }
        }
      }
    }

    friend std::istream& operator>>(std::istream& is, Graph& g);

    int GetDistance(int k) const {
      return distance_[k - 1];
    }

    int GetParents(int k) const {
      return parents_[k - 1];
    }

    void ParentsSearch(int start, int end) {
      --start;
      --end;

      if (start == end) {
        std::cout << start + 1;
        return;
      }

      if (parents_[end] == -1) {
        return;
      }

      std::stack<int> answer;
      int curr = end;

      while (curr != start) {
        answer.push(curr);
        curr = parents_[curr];
      }
      std::cout << start + 1 << " ";

      while (!answer.empty()) {
        std::cout << answer.top() + 1 << " ";
        answer.pop();
      }
    }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);
  g.vertexes_[end].insert(begin);
  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  int start, end;
  std::cin >> start >> end;
  Graph graph(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> graph;
  }

  graph.BFS(start);

  std::cout << (graph.GetDistance(end) == 100000000 ? -1 : graph.GetDistance(end)) << "\n";
  graph.ParentsSearch(start, end);

  return 0;
}
