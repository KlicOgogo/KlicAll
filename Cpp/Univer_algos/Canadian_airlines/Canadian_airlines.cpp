#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

int sgn(int y) {
    if (y > 0) {
        return 1;
    } else if (y == 0) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    std::ifstream fin("in.txt");
    int n, m;
    fin >> n >> m;
    std::vector<std::string> cities(n);
    for (int i = 0; i < n; i++) {
        fin >> cities[i];
    }
    std::vector< std::vector <int> > dp_matrix(n);
    std::vector< std::vector <int> > flight_graph(n);
    for (int i = 0; i < n; i++) {
        dp_matrix[i].resize(n);
        flight_graph[i].resize(n);
    }
    for (int i = 0; i < m; i++) {
        std::string from, to;
        fin >> from >> to;
        int find_from = std::find(cities.begin(), cities.end(), from)-cities.begin();
        int find_to = std::find(cities.begin(), cities.end(), to)-cities.begin();
        flight_graph[find_from][find_to] = 1;
        flight_graph[find_to][find_from] = 1;
    }
    dp_matrix[0][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i+1; j++) {
	        std::vector<int> maxes;
            for (int k = 0; k < i; k++) {
                if (k == 0 || k != j) {
                    maxes.push_back((dp_matrix[k][j]*sgn(flight_graph[k][i])+flight_graph[k][i])*sgn(dp_matrix[k][j]));
                }
            }
            int best_max = *(std::max_element(maxes.begin(), maxes.end()));
            if (i == j) {
                dp_matrix[i][j] = dp_matrix[j][i] = std::max(best_max-1, dp_matrix[i][j]);
            } else {
                dp_matrix[i][j] = dp_matrix[j][i] = std::max(best_max, dp_matrix[i][j]);
            }
        }
    }
    std::ofstream fout("out.txt");
    if (dp_matrix[n-1][n-1] == 0) {
        fout << "No solution";
    } else {
        fout << dp_matrix[n-1][n-1];
    }
    fout.close();
    return 0;
}
