#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

struct Cell {
    bool l, r, u, d; //0 - closed, 1 - opened;
    Cell() = default;
    Cell(bool left, bool right, bool up, bool down): l(left), r(right), u(up), d(down) {}
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> field(2 * n + 1, std::vector<char>(2 * m + 1));
    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < 2 * m + 1; ++j) {
            std::cin >> field[i][j];
        }
    }
    std::unordered_map<int, Cell> graph;
    std::unordered_map<char, bool> ch_b;
    ch_b['|'] = false;
    ch_b['-'] = false;
    ch_b['.'] = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            graph[i * m * n + j] = Cell(ch_b[field[2 * i + 1][2 * j]], ch_b[field[2 * i + 1][2 * (j+1)]],
                    ch_b[field[2 * i][2 * j + 1]], ch_b[field[2 * (i+1)][2 * j + 1]]);
        }
    }
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    int visited_count = 1;
    std::queue<int> bfs;
    bfs.push(0);
    visited[0][0] = true;
    while (visited_count < n * m) {
        int top = bfs.front();
        bfs.pop();
        int x = top / m / n;
        int y = top % (m * n);
        auto cur_cell = graph[top];
        if (cur_cell.l && ! visited[x][y-1]) {
            visited[x][y-1] = true;
            bfs.push(x * m * n + y - 1);
            ++visited_count;
        }
        if (cur_cell.r && ! visited[x][y+1]) {
            visited[x][y+1] = true;
            bfs.push(x * m * n + y + 1);
            ++visited_count;
        }
        if (cur_cell.u && ! visited[x-1][y]) {
            visited[x-1][y] = true;
            bfs.push((x-1) * m * n + y);
            ++visited_count;
        }
        if (cur_cell.d && ! visited[x+1][y]) {
            visited[x+1][y] = true;
            bfs.push((x+1) * m * n + y);
            ++visited_count;
        }
        if (bfs.empty()) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (visited[i][j]) {
                        if (j > 0 && !visited[i][j-1]) {
                            bfs.push(i * m * n + j - 1);
                            visited[i][j-1] = true;
                            ++visited_count;
                            field[2 * i + 1][2 * j] = '.';
                        } else if (j < m-1 && !visited[i][j+1]) {
                            bfs.push(i * m * n + j + 1);
                            visited[i][j+1] = true;
                            ++visited_count;
                            field[2 * i + 1][2 * (j+1)] = '.';
                        } else if (i < n-1 && !visited[i+1][j]) {
                            bfs.push((i+1) * m * n + j);
                            visited[i+1][j] = true;
                            ++visited_count;
                            field[2 * (i + 1)][2 * j+ 1] = '.';
                        } else if (i > 0 && !visited[i-1][j]) {
                            bfs.push((i-1) * m * n + j);
                            visited[i-1][j] = true;
                            ++visited_count;
                            field[2 * i][2 * j + 1] = '.';
                        }
                    }
                    if (!bfs.empty()) {
                        break;
                    }
                }
                if (!bfs.empty()) {
                    break;
                }
            }
        }
    }
    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < 2 * m + 1; ++j) {
            std::cout << field[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}