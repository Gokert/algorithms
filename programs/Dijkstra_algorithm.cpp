/* "Cities".
It is required to find the most profitable route between cities.
Requirements: running time O((N+M)logN), where N is the number of cities, M is the known roads between them.
Input data format.
The first line contains the number N - the number of cities.
The second line contains the number M - the number of roads.
Each next line contains a description of the road (from where, where, travel time).
The last line contains the route (from where and where to get to).
Output data format.
Print the length of the most profitable route.

For example:

in        out
6         9
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2

*/


#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class list_graph {
public:
  explicit list_graph(int num);

  int vertexCount() const;
  void add(int from, int to, int weight);
  std::vector<std::pair<int, int>> getNext(int vertex) const;

private:
  std::vector<std::vector<std::pair<int, int>>> neighbors;

};

list_graph::list_graph(int num) : neighbors(num) {}

int list_graph::vertexCount() const { 
    return neighbors.size(); 
}

std::vector<std::pair<int, int>> list_graph::getNext(int vertex) const {
  if (vertex < 0 || vertex >= neighbors.size()) {
    return {};
  }
  return neighbors[vertex];
}

void list_graph::add(int from, int to, int weight) {
  if (to < 0 || to >= neighbors.size() || from < 0 ||
      from >= neighbors.size()) {
    return;
  }
  neighbors[from].push_back(std::make_pair(weight, to));
  neighbors[to].push_back(std::make_pair(weight, from));
}

int Dijk(list_graph &list_graph, int start, int end) {
  int inf = std::numeric_limits<int>::max();
  std::vector<int> top(list_graph.vertexCount(), -1);
  std::vector<int> length(list_graph.vertexCount(), inf);
  length[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,std::greater<>> queue;

  queue.push({0, start});
  while (!queue.empty()) {
    int u = queue.top().second;
    queue.pop();

    for (auto &it : list_graph.getNext(u)) {
      int w = it.first;
      int v = it.second;
      if (length[v] > length[u] + w) {
        length[v] = length[u] + w;

        top[v] = u;
        queue.push({length[v], v});
      }
    }
  }

  if (length[end] == inf) {
    return -1;
  } else {
    return length[end];
  }
}

void task() {
  int n = 0;
  int m = 0;
  std::cin >> n;
  std::cin >> m;
  list_graph list_graph(n);

  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;
    list_graph.add(from, to, weight);
  }
  int start = 0, end = 0;
  std::cin >> start >> end;

  std::cout << Dijk(list_graph, start, end);
}

int main() {
  task();

  return 0;
}
