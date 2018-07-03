#include <fstream>
#include <vector>

std::vector<int**> matrixes;

bool nonZero(int** matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void solve(int** matrix, int m, int n) {
    if (nonZero(matrix, m, n)) {
        int** good_matrix = new int*[m];
        for (int i = 0; i < m; i++) {
            good_matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                good_matrix[i][j] = matrix[i][j];
                if (good_matrix[i][j] == 9) {
                    good_matrix[i][j] = 0;
                }
            }
        }
        matrixes.push_back(good_matrix);
        return;
    } else {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    //case 1
                    if (i <= m-2 && j <= n-2 &&
                        matrix[i+1][j] == 0 && matrix[i+1][j+1] == 0) {
                        matrix[i][j] = 1;
                        matrix[i+1][j] = 1;
                        matrix[i+1][j+1] = 1;
                        solve(matrix, m, n);
                        matrix[i+1][j] = 0;
                        matrix[i+1][j+1] = 0;
                        matrix[i][j] = 0;
                    }
                    //case 2
                    if (i <= m-2 && j <= n-2 &&
                        matrix[i][j+1] == 0 && matrix[i+1][j+1] == 0) {
                        matrix[i][j] = 2;
                        matrix[i][j+1] = 2;
                        matrix[i+1][j+1] = 2;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i][j+1] = 0;
                        matrix[i+1][j+1] = 0;
                    }
                    //case 3
                    if (i <= m-2 && j >= 1 &&
                        matrix[i+1][j] == 0 && matrix[i+1][j-1] == 0) {
                        matrix[i][j] = 3;
                        matrix[i+1][j] = 3;
                        matrix[i+1][j-1] = 3;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i+1][j] = 0;
                        matrix[i+1][j-1] = 0;
                    }
                    //case 4
                    if (i <= m-2 && j <= n-2 &&
                        matrix[i+1][j] == 0 && matrix[i][j+1] == 0) {
                        matrix[i][j] = 4;
                        matrix[i+1][j] = 4;
                        matrix[i][j+1] = 4;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i+1][j] = 0;
                        matrix[i][j+1] = 0;
                    }
                    //case 5
                    if (i <= m-3 && j <= n-2 && matrix[i+1][j] == 0 &&
                        matrix[i+2][j] == 0 && matrix[i+1][j+1] == 0) {
                        matrix[i][j] = 5;
                        matrix[i+1][j] = 5;
                        matrix[i+2][j] = 5;
                        matrix[i+1][j+1] = 5;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i+1][j] = 0;
                        matrix[i+2][j] = 0;
                        matrix[i+1][j+1] = 0;
                    }
                    //case 6
                    if (i <= m-3 && j>=1 && matrix[i+1][j] == 0 &&
                        matrix[i+2][j] == 0 && matrix[i+1][j-1] == 0) {
                        matrix[i][j] = 6;
                        matrix[i+1][j] = 6;
                        matrix[i+2][j] = 6;
                        matrix[i+1][j-1] = 6;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i+1][j] = 0;
                        matrix[i+2][j] = 0;
                        matrix[i+1][j-1] = 0;
                    }
                    //case 7
                    if (i <= m-2 && j <= n-3 && matrix[i][j+1] == 0 &&
                        matrix[i][j+2] == 0 && matrix[i+1][j+1] == 0) {
                        matrix[i][j] = 7;
                        matrix[i][j+1] = 7;
                        matrix[i][j+2] = 7;
                        matrix[i+1][j+1] = 7;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i][j+1] = 0;
                        matrix[i][j+2] = 0;
                        matrix[i+1][j+1] = 0;
                    }
                    //case 8
                    if (i <= m-2 && j >= 1 && j <= n-2 &&
                        matrix[i+1][j-1] == 0 && matrix[i+1][j] == 0 && matrix[i+1][j+1] == 0) {
                        matrix[i][j] = 8;
                        matrix[i+1][j-1] = 8;
                        matrix[i+1][j] = 8;
                        matrix[i+1][j+1] = 8;
                        solve(matrix, m, n);
                        matrix[i][j] = 0;
                        matrix[i+1][j-1] = 0;
                        matrix[i+1][j] = 0;
                        matrix[i+1][j+1] = 0;
                        return;
                    }
                    else {
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    std::ifstream fin("input.txt");
    int n, m;
    fin >> n >> m;
    int** matrix = new int*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            char t;
            fin >> t;
            matrix[i][j] = t-48;
            if (matrix[i][j] == 1) {
                matrix[i][j] = 9;
            }
        }
    }
    fin.close();
    solve(matrix, m, n);
    std::ofstream fout("output.txt");
    fout << matrixes.size() << '\n';
    for (int i = 0; i < matrixes.size(); i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                fout << matrixes[i][j][k];
            }
            fout << '\n';
        }
        fout << '\n';
    }
    fout.close();
    return 0;
}
