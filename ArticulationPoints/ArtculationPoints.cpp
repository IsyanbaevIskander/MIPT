#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

class Vertex {
public:
    inline static int time;
    int index;
    int time_in = 0;
    int time_up = 0;
    bool visited = false;
};

class Graph {
private:
    std::vector<std::unordered_set<int>> edges_;
    std::set<int> articulation_points_;
    std::vector<Vertex> vertexes_;

public:
    explicit Graph(int n) {
      edges_ = std::vector<std::unordered_set<int>>(n);
      articulation_points_ = std::set<int>();
      vertexes_ = std::vector<Vertex>(n);

      for (int i = 0; i < n; ++i) {
        vertexes_[i].index = i + 1;
      }

      Vertex::time = 0;
    }

    void DFS(int vertex, bool is_root) {
      vertexes_[vertex].visited = true;
      vertexes_[vertex].time_in = vertexes_[vertex].time_up = ++Vertex::time;
      int children = 0;

      for (auto neighbour : edges_[vertexes_[vertex].index - 1]) {

        if (vertexes_[neighbour].visited) {
          vertexes_[vertex].time_up = std::min(vertexes_[vertex].time_up, vertexes_[neighbour].time_in);
        } else {
          ++children;
          DFS(neighbour, false);
          vertexes_[vertex].time_up = std::min(vertexes_[vertex].time_up, vertexes_[neighbour].time_up);

          if (!is_root && vertexes_[vertex].time_in <= vertexes_[neighbour].time_up) {
            articulation_points_.insert(vertexes_[vertex].index);
          }
        }
      }

      if (is_root && children > 1) {
        articulation_points_.insert(vertexes_[vertex].index);
      }
    }

    friend std::istream& operator>>(std::istream& is, Graph& g);

    size_t GetSize() {
      return articulation_points_.size();
    }

    void GetArticulationPoints() {
      for (auto i : articulation_points_) {
        std::cout << i << "\n";
      }
    }

    void DoDFS(int n) {
      for (int i = 0; i < n; ++i) {
        if (!vertexes_[i].visited) {
          DFS(i, true);
        }
      }
    }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.edges_[begin].insert(end);
  g.edges_[end].insert(begin);
  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> graph;
  }

  graph.DoDFS(n);

  std::cout << graph.GetSize() << "\n";
  graph.GetArticulationPoints();
  return 0;
}
