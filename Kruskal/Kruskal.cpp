#include <iostream>
#include <vector>

class CDS {
private:
    std::vector<int> parents_;
    std::vector<int> rank_;

public:
    explicit CDS(size_t n) {
      rank_ = std::vector<int>(n, 0);
      parents_ = std::vector<int>(n);
      for (int i = 0; i < n; ++i) {
        parents_[i] = i;
      }
    };

    int FindSet(int x) {
      if (x == parents_[x]) {
        return x;
      }

      return parents_[x] = FindSet(parents_[x]);
    }

    void Union(int x, int y) {
      x = FindSet(x);
      y = FindSet(y);

      if (rank_[x] < rank_[y]) {
        parents_[x] = y;
      } else if (rank_[x] > rank_[y]) {
        parents_[y] = x;
      } else {
        parents_[x] = y;
        ++rank_[y];
      }
    }
};

struct Edge {
public:
    int weight_;
    int first_;
    int second_;

    bool operator<(const Edge& other) const {
      return weight_ < other.weight_;
    }
};

struct Graph {
public:
    std::vector<Edge> edges_;
    std::vector<Edge> MST_;
    int MSTweight = 0;
    int edges_number_;
    int vertexes_number_;
    bool is_ready = false;

    explicit Graph(int m, int n) : edges_number_(m), vertexes_number_(n) {
      edges_ = std::vector<Edge>(m);
      MST_ = std::vector<Edge>(m);
    }
};

void FindMST(Graph& graph) {
  CDS cds(graph.edges_number_);

  for (auto edge : graph.edges_) {
    if (graph.is_ready) {
      return;
    }

    if (cds.FindSet(edge.first_) != cds.FindSet(edge.second_)) {
      cds.Union(edge.first_, edge.second_);
      graph.MST_.push_back(edge);
      graph.MSTweight += edge.weight_;

      if (int(graph.MST_.size()) - graph.edges_number_ == graph.vertexes_number_ - 1) {
        graph.is_ready = true;
      }
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  Graph graph(m, n);

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    graph.edges_[i].first_ = u;
    graph.edges_[i].second_ = v;
    graph.edges_[i].weight_ = w;
  }

  FindMST(graph);
  std::cout << graph.MSTweight;
  return 0;
}
