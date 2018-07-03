#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>

typedef std::vector<std::list<int> > Graph;

Graph unreachable_from_terminal(const Graph &graph, int terminal) {
    std::vector<bool> visited(graph.size());
    std::queue<int> bfs;
    bfs.push(terminal);
    visited[0] = true;
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        for (auto it = graph[cur].begin(); it != graph[cur].end(); it++) {
            if (!visited[*it]) {
                visited[*it] = true;
                bfs.push(*it);
            }
        }
    }
    std::unordered_map<int, int> new_vertex;
    int unreachable_count = 0;
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            new_vertex[i] = unreachable_count;
            unreachable_count++;
        }
    }
    Graph graph_on_unreachable((size_t) unreachable_count);
    for (int i = 0, j = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
                if (!visited[*it]) {
                    graph_on_unreachable[j].push_back(new_vertex[*it]);
                }
            }
            j++;
        }
    }
    return graph_on_unreachable;
}

Graph on_reversed_arcs(const Graph &graph) {
    Graph reversed_graph(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            reversed_graph[*it].push_back(i);
        }
    }
    return reversed_graph;
}

std::vector<int> top_sort(const Graph &graph) {
    std::vector<std::list<int>::const_iterator> adj_vector_iterator(graph.size());
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
            while (it != graph[top].end() && visited[*it]) {
                it++;
            }
            if (it != graph[top].end()) {
                dfs.push(*it);
                visited[*it] = true;
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

Graph condensation(const Graph &graph) {
    std::vector<int> top_order = top_sort(graph);
    Graph reversed = on_reversed_arcs(graph);
    std::vector<std::list<int>::const_iterator> adj_vector_iterator(reversed.size());
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
            while (it != reversed[top].end() && visited[*it]) {
                it++;
            }
            if (it != reversed[top].end()) {
                dfs.push(*it);
                visited[*it] = true;
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
    Graph condensated(size_t(component_count) + 1);
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            condensated[component_number[i]].push_back(component_number[*it]);
        }
    }
    return condensated;
}

int count_edges_to_reach_all(const Graph &graph) {
    Graph unreachable_graph = unreachable_from_terminal(graph, 0);
    if (unreachable_graph.size() == 0) {
        return 0;
    }
    Graph condensated = condensation(unreachable_graph);
    std::vector<int> top_order = top_sort(condensated);
    std::vector<std::list<int>::const_iterator> adj_vector_iterator(condensated.size());
    for (int i = 0; i < condensated.size(); i++) {
        adj_vector_iterator[i] = condensated[i].begin();
    }
    std::vector<bool> visited(condensated.size());
    std::stack<int> dfs;
    dfs.push(top_order[0]);
    visited[top_order[0]] = true;
    int time = 1;
    int last_unvisited = 1;
    int components_to_connect = 0;
    while (time < 2 * condensated.size()) {
        if (dfs.empty()) {
            components_to_connect++;
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
            while (it != condensated[top].end() && visited[*it]) {
                it++;
            }
            if (it != condensated[top].end()) {
                dfs.push(*it);
                visited[*it] = true;
                while (last_unvisited < top_order.size() && visited[top_order[last_unvisited]]) {
                    last_unvisited++;
                }
                adj_vector_iterator[top] = ++it;
            } else {
                dfs.pop();
            }
            time++;
        }
    }
    return ++components_to_connect;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    int from, to;
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    int count = count_edges_to_reach_all(graph);
    std::cout << count << '\n';
    return 0;
}