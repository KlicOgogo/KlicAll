#include <iostream>
#include <vector>
#include <queue>

int main() {
    size_t n, m;
    std::cin >> n >> m;
    if (m == 0) {
        if (n != 2) {
            std::cout << -1;
        } else {
            std::cout << 1 << '\n';
            std::cout << 1 << '\n';
            std::cout << 2;
        }
        return 0;
    }
    std::vector<std::vector<bool>> graph(n, std::vector<bool>(n));
    int from, to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        graph[from-1][to-1] = graph[to-1][from-1] = true;
    }
    std::vector<bool> visited(n);
    std::vector<int> part(n);
    std::queue<int> bfs;
    bfs.push(0);
    visited[0] = true;
    part[0] = 1;
    bool yes = true;
    int visited_count = 1;
    int min_unvisited = 1;
    while(!bfs.empty() and visited_count < n) {
        int top = bfs.front();
        bfs.pop();
        for (int i = 0; i < n; ++i) {
            if (graph[top][i] == 0 and top != i) {
                if (!visited[i]) {
                    part[i] = -part[top];
                    bfs.push(i);
                    visited[i] = true;
                    ++visited_count;
                    while (visited[min_unvisited]) {
                        ++min_unvisited;
                    }
                } else {
                    if (part[i] == part[top]) {
                        yes = false;
                    }
                }
            }
        }
        if (bfs.empty()) {
            bfs.push(min_unvisited);
            visited[min_unvisited] = true;
            ++visited_count;
            part[min_unvisited] = -1;
            while (visited[min_unvisited]) {
                ++min_unvisited;
            }
        }
    }
    if (!yes) {
        std::cout << -1;
        return 0;
    } else {
        int ones = 0;
        for (int i =0; i < n; ++i) {
            if (part[i] == 1) {
                ++ones;
            }
        }
        std::cout << ones << '\n';
        for (int i = 0; i < n; ++i) {
            if (part[i] == 1) {
                std::cout << i+1 << ' ';
            }
        }
        std::cout << '\n';
        for (int i = 0; i < n; ++i) {
            if (part[i] == -1) {
                std::cout << i+1 << ' ';
            }
        }
    }
    return 0;
}