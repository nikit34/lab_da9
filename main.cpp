#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <chrono>


bool BFS(std::vector<std::vector<int> > &graph, uint64_t& start, uint64_t& end, std::vector<int> &parent) {
    std::vector<bool> visited(graph.size());
    std::queue <int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;
    int u;

    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (int v = 1; v < graph.size(); ++v) {
            if (!visited[v] && graph[u][v]) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[end];
}

bool DFS(std::vector<std::vector<int> > &graph, std::vector<int> &parent, std::vector<bool>& visited, uint64_t x, uint64_t t) {
    if (x == t)
        return true;
    visited[x] = true;

    for (uint64_t i = 1; i < graph.size(); ++i) {
        if (graph[x][i] > 0 && !visited[i]) {
            parent[i] = x;
            if (DFS(graph, parent, visited, i, t))
                return true;
        }
    }
    return false;
}

uint64_t FordFulkerson(std::vector<std::vector<int> > &graph, uint64_t&& start, uint64_t& end) {
    int u, v;
    uint64_t maxFlow = 0;
    int flow;
    std::vector<std::vector<int> > resGraph = graph;
    std::vector<int> parent(graph.size());

    // std::vector<bool> visited(graph.size());
    // while (DFS(resGraph, parent, visited, start, end)){
    while (BFS(resGraph, start, end, parent)) {
        flow = std::numeric_limits<int>::max();

        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            flow = std::min(flow, resGraph[u][v]);
        }

        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            resGraph[u][v] -= flow;
            resGraph[v][u] += flow;
        }

        maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint64_t n, m;
    int from, to;
    std::cin >> n >> m;

    std::vector<std::vector<int> > graph(n + 1);
    for (uint64_t i = 0; i < n + 1; ++i) {
        graph[i].resize(n + 1);
    }

    for (uint64_t i = 0; i < m; ++i) {
        std::cin >> from >> to;
        std::cin >> graph[from][to];
    }
    std::cout << FordFulkerson(graph, 1, n) << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << std::endl << "time: " << duration.count() << std::endl;

    return 0;
}
