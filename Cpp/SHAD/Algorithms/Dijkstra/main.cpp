#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>

int main() {
    std::ifstream cin("input.txt");
    size_t vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    std::vector< std::vector<long double> > dist_matrix(vertex_count);
    for (int i = 0; i < vertex_count; i++) {
        dist_matrix[i].resize(vertex_count, INT_MAX);
    }
    int v1, v2;
    long double  w;
    for (int i = 0; i < edge_count; i++) {
        cin >> v1 >> v2 >> w;
        dist_matrix[v1-1][v2-1] = w;
    }
    cin.close();
    std::vector<long double> min_dist(vertex_count, INT_MAX);
    std::vector<uint64_t> path(vertex_count, INT_MAX);
    min_dist[0] = 0;
    path[0] = -1;
    std::vector<int> found;
    found.reserve(vertex_count);
    found.push_back(0);
    std::vector<int> to_find(vertex_count-1);
    for (int i = 0; i < vertex_count-1; i++) {
        to_find[i] = i+1;
    }
    while (found.size() != vertex_count) {
        std::vector<long double> relaxed_dist(to_find.size());
        for (int i = 0; i < to_find.size(); i++) {
            if (min_dist[found.back()] + dist_matrix[found.back()][to_find[i]] < min_dist[to_find[i]]) {
                min_dist[to_find[i]] = min_dist[found.back()] + dist_matrix[found.back()][to_find[i]];
                path[to_find[i]] = found.back();
            }
            relaxed_dist[i] = min_dist[to_find[i]];
        }
        int index_min = std::min_element(relaxed_dist.begin(), relaxed_dist.end()) - relaxed_dist.begin();
        found.push_back(to_find[index_min]);
        to_find.erase(to_find.begin()+index_min);
    }
    std::cout << "Min distances from vertex 1:\n";
    for (int i = 1; i < vertex_count; i++) {
        std::cout << min_dist[i] << ' ';
    }
    std::cout << '\n';
    int cur = 8;
    std::vector<int> path_;
    while (cur != -1) {
        path_.push_back(cur+1);
        cur = path[cur];
    }
    std::reverse(path_.begin(), path_.end());
    std::cout << "The shortest path from vertex 1 to vertex 9:\n";
    for (int i = 0; i < path_.size(); i++) {
        std::cout << path_[i] << ' ';
    }
    return 0;
}