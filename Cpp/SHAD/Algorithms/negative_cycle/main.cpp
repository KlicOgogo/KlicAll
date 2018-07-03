#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <climits>

typedef std::vector<std::unordered_map<int, int64_t>> Graph;

Graph on_reversed_arcs(const Graph &graph) {
    Graph reversed_graph(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            reversed_graph[it->first][i] = it->second;
        }
    }
    return reversed_graph;
}

std::vector<int> top_sort(const Graph &graph) {
    std::vector<std::unordered_map<int, int64_t>::const_iterator> adj_vector_iterator(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        adj_vector_iterator[i] = graph[i].begin();
    }
    std::vector<int> top_order(graph.size());
    std::vector<bool> visited(graph.size());
    std::stack<int> dfs;
    dfs.push(0);
    visited[0] = true;
    int time = 1;
    int last_unvisited = 1;
    int top_order_index = (int) graph.size() - 1;
    while (time < 2 * graph.size()) {
        if (dfs.empty()) {
            dfs.push(last_unvisited);
            visited[last_unvisited] = true;
            time++;
            while (last_unvisited < visited.size() && visited[last_unvisited]) {
                last_unvisited++;
            }
        }
        while (!dfs.empty()) {
            int top = dfs.top();
            auto it = adj_vector_iterator[top];
            while (it != graph[top].end() && visited[it->first]) {
                it++;
            }
            if (it != graph[top].end()) {
                dfs.push(it->first);
                visited[it->first] = true;
                while (last_unvisited < visited.size() && visited[last_unvisited]) {
                    last_unvisited++;
                }
                adj_vector_iterator[top] = ++it;
            } else {
                dfs.pop();
                top_order[top_order_index] = top;
                top_order_index--;
            }
            time++;
        }
    }
    return top_order;
}

std::vector<Graph> strongly_connected_components(const Graph &graph, std::vector<std::vector<int>> &old_vertex_number) {
    std::vector<int> top_order = top_sort(graph);
    Graph reversed = on_reversed_arcs(graph);
    std::vector<std::unordered_map<int, int64_t>::const_iterator> adj_vector_iterator(reversed.size());
    for (int i = 0; i < reversed.size(); i++) {
        adj_vector_iterator[i] = reversed[i].begin();
    }
    std::vector<bool> visited(reversed.size());
    std::stack<int> dfs;
    dfs.push(top_order[0]);
    visited[top_order[0]] = true;
    int time = 1;
    int last_unvisited = 1;
    std::vector<int> component_number(reversed.size());
    int component_count = 0;
    while (time < 2 * reversed.size()) {
        if (dfs.empty()) {
            component_count++;
            dfs.push(top_order[last_unvisited]);
            visited[top_order[last_unvisited]] = true;
            time++;
            while (last_unvisited < top_order.size() && visited[top_order[last_unvisited]]) {
                last_unvisited++;
            }
        }
        while (!dfs.empty()) {
            int top = dfs.top();
            auto it = adj_vector_iterator[top];
            while (it != reversed[top].end() && visited[it->first]) {
                it++;
            }
            if (it != reversed[top].end()) {
                dfs.push(it->first);
                visited[it->first] = true;
                while (last_unvisited < top_order.size() && visited[top_order[last_unvisited]]) {
                    last_unvisited++;
                }
                adj_vector_iterator[top] = ++it;
            } else {
                dfs.pop();
                component_number[top] = component_count;
            }
            time++;
        }
    }
    std::unordered_map<int, int> new_vertex_number;
    std::vector<int> each_component_count((size_t) component_count + 1);
    for (int i = 0; i < component_number.size(); i++) {
        new_vertex_number[i] = each_component_count[component_number[i]];
        each_component_count[component_number[i]]++;
    }
    std::vector<Graph> components((size_t) component_count + 1);
    old_vertex_number.resize((size_t) component_count + 1);
    for (int i = 0; i < component_count + 1; i++) {
        components[i].resize((size_t) each_component_count[i]);
        old_vertex_number[i].resize((size_t) each_component_count[i]);
    }
    for (int i = 0; i < reversed.size(); i++) {
        old_vertex_number[component_number[i]][new_vertex_number[i]] = i;
        std::unordered_map<int, int64_t> new_list;
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            if (component_number[it->first] == component_number[i]) {
                new_list[new_vertex_number[it->first]] = it->second;
            }
        }
        components[component_number[i]][new_vertex_number[i]] = new_list;
    }
    return components;
}

bool has_negative_cycle(const Graph &graph, const std::vector<int> &old_numbers,
                        int &neg_cycle_min_vertex, int terminal) {
    if (terminal >= graph.size()) {
        throw std::runtime_error("Incorrect terminal number!");
    }
    std::vector<int64_t> min_dist(graph.size(), INT_MAX);
    min_dist[terminal] = 0;
    bool has_neg_cycle = false;
    neg_cycle_min_vertex = INT_MAX;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            for (auto it = graph[j].begin(); it != graph[j].end(); it++) {
                if (min_dist[it->first] > min_dist[j] + it->second) {
                    min_dist[it->first] = min_dist[j] + it->second;
                    if (i == graph.size() - 1) {
                        has_neg_cycle = true;
                    }
                }
            }
        }
    }
    neg_cycle_min_vertex = *std::min_element(old_numbers.begin(), old_numbers.end());
    return has_neg_cycle;
}

bool has_negative_cycle(const Graph &graph, int &neg_cycle_min_vertex) {
    std::vector<std::vector<int> > old_vertex;
    std::vector<Graph> components = strongly_connected_components(graph, old_vertex);
    bool has_neg_cycle = false;
    neg_cycle_min_vertex = INT_MAX;
    int cur_min_vertex;
    for (int i = 0; i < components.size(); i++) {
        if (has_negative_cycle(components[i], old_vertex[i], cur_min_vertex, 0)) {
            has_neg_cycle = true;
            neg_cycle_min_vertex = std::min(neg_cycle_min_vertex, cur_min_vertex);
        }
    }
    neg_cycle_min_vertex++;
    return has_neg_cycle;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    int from, to;
    int64_t cost;
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to >> cost;
        if (graph[from - 1].find(to - 1) == graph[from - 1].end()) {
            graph[from - 1][to - 1] = cost;
        } else {
            graph[from - 1][to - 1] = std::min(graph[from - 1][to - 1], cost);
        }
    }
    int min_vertex;
    bool has = has_negative_cycle(graph, min_vertex);
    if (has) {
        std::cout << "YES\n" << min_vertex << '\n';
    } else {
        std::cout << "NO\n";
    }
    return 0;
}