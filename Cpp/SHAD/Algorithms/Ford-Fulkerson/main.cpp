#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>
#include <list>
#include <unordered_map>

class Network {
public:
    Network(std::string filename) {
        std::ifstream cin(filename);
        cin >> v_count >> e_count >> s >> t;
        s--;
        t--;
        adj_lists.resize(v_count);
        uint64_t from, to;
        int ub;
        for (int i = 0; i < e_count; i++) {
            cin >> from >> to >> ub;
            adj_lists[from-1].push_back(int(to-1));
            adj_lists[to-1].push_back(int(from-1));
            upper_bounds[(from - 1) * v_count + to - 1] = ub;
            upper_bounds[(to - 1) * v_count + from - 1] = 0;
        }
        cin.close();
    }
    int max_flow() {
        int ans = 0;
        std::vector<int> path(v_count, -1);
        while (this->has_positive_path(path)) {
            int l_bound = find_min_ub_in_path(path);
            ans += l_bound;
            reload_upper_bounds(path, l_bound);
            path.assign(v_count, -1);
        }
        return ans;
    }
private:
    std::unordered_map<uint64_t, int> upper_bounds;
    std::vector<std::list<int>> adj_lists;
    uint64_t v_count, e_count;
    int s, t;
    int find_min_ub_in_path(const std::vector<int>& path) {
        int min = INT_MAX;
        int temp = t;
        while (temp != s) {
            min = std::min(min, upper_bounds[v_count * path[temp] + temp]);
            temp = path[temp];
        }
        return min;
    }
    void reload_upper_bounds(const std::vector<int>& path, int l_bound) {
        int temp = t;
        while (temp != s) {
            upper_bounds[v_count * path[temp] + temp] -= l_bound;
            upper_bounds[v_count * temp + path[temp]] += l_bound;
            temp = path[temp];
        }
    }
    bool has_positive_path(std::vector<int>& path) {
        std::vector<bool> visited(v_count);
        std::queue<int> bfs;
        bfs.push(s);
        visited[s] = true;
        while (!bfs.empty() && !visited[t]) {
            int top = bfs.front();
            bfs.pop();
            for (auto it = adj_lists[top].begin(); it != adj_lists[top].end(); it++) {
                if (upper_bounds[v_count * top + *it] > 0 && !visited[*it]) {
                    visited[*it] = true;
                    path[*it] = top;
                    bfs.push(*it);
                }
            }
        }
        if (visited[t]) {
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    Network net("input.txt");
    int result = net.max_flow();
    std::cout << result << '\n';
    return 0;
}