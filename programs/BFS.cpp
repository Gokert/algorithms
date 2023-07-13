/*
The number of different paths.
An unweighted undirected graph is given. A graph can have several shortest paths between some vertices. Find the number of different shortest paths between the given vertices.
Requirements: O(V+E) complexity.
Input format.
  v: number of vertices (max. 50000),
  n: number of ribs (max. 200000),
  n pairs of edge vertices,
  a pair of vertices u, w for the query.

Output format.
  The number of shortest paths from u to w.

For example:
in          out
4           2
5
0 1
0 2
1 2
1 3
2 3

0 3

*/

#include <iostream>
#include <queue>
#include <vector>

class IGraph {
public:
  virtual void add(const int from, const int to) = 0;
  virtual int pointCount() const = 0;
  virtual std::vector<int> getNext(const int points) const = 0;
  virtual ~IGraph() {}
};

class ListGraph : public IGraph {
public:
  ListGraph(int count);

  void add(const int from, const int to) override;
  int pointCount() const override;
  std::vector<int> getNext(const int points) const override;
  
private:
  std::vector<std::vector<int>> list_graph;


};

ListGraph::ListGraph(int count) { 
  list_graph.resize(count); 
}

void ListGraph::add(int from, int to) { 
  list_graph[from].push_back(to); 
  }

int ListGraph::pointCount() const { 
  return list_graph.size(); 
}

std::vector<int> ListGraph::getNext(int points) const {
  return list_graph[points];
}

int bfs(const IGraph& listGraph, int from, int to) {
  std::vector<std::pair<int, int>> explored_nodes(listGraph.pointCount(), {0, 0});
  std::queue<int> q;

  q.push(from);
  explored_nodes[from].second = 1;

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    if (current == to) {
      break;
    }

    for (const auto& next : listGraph.getNext(current)) 
    {
      if (explored_nodes[next].first == 0) 
      {
        explored_nodes[next].first = explored_nodes[current].first + 1;
        explored_nodes[next].second = explored_nodes[current].second;
        q.push(next);

      } else if (explored_nodes[next].first == explored_nodes[current].first + 1) 
      {
        explored_nodes[next].second += explored_nodes[current].second;
      }
    }
  }

  return explored_nodes[to].second;
}

void task() {
  int num_vert = 0;
  int num = 0;
  std::cin >> num_vert >> num;

  ListGraph graph(num_vert);

  for (int i = 0; i < num; ++i) {
    int from = 0;
    int to = 0;
    std::cin >> from >> to;

    graph.add(from, to);
    graph.add(to, from);
  }

  int start_vert = 0, end_vertex = 0;
  std::cin >> start_vert >> end_vertex;

  int path_count = bfs(graph, start_vert, end_vertex);

  std::cout << path_count << std::endl;
}

int main(void) {
  task();

  return 0;
}
