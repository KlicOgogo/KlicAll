#include <fstream>
#include <algorithm>
#include <vector>

int main() {
    std::ifstream fin("in.txt");
    int m, n;
    fin >> n >> m;
    std::vector<int> buttons(m);
    for (int i = 0; i < m; i++) {
        fin >> buttons[i];
    }
    fin.close();
    std::vector< std::vector<int> > dp_matrix(n);
    for (int i = 0; i < n; i++) {
        dp_matrix[i].resize(m-n+1);
    }
    dp_matrix[0][0] = buttons[m-1];
    int temp = buttons[m-1];
    for (int i = 1; i < m-n+1; i++) {
        temp += buttons[m-1-i];
        dp_matrix[0][i] = dp_matrix[0][i-1] + temp;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m-n+1; j++) {
            std::vector<int> p(1);
            p.reserve(j+1);
            for (int k = 0; k < j+1; k++) {
                p.push_back(p[p.size()-1] + (k+1) * buttons[m-1-i-j+k]);
            }
            std::vector<int> mins;
            mins.reserve(j+1);
            for (int k = 0; k < j+1; k++) {
                mins.push_back(dp_matrix[i-1][k] + p[p.size()-1-k]);
            }
            dp_matrix[i][j] = *(std::min_element(mins.begin(), mins.end()));
        }
    }
    std::ofstream fout("out.txt");
    fout << dp_matrix[n-1][m-n];
    fout.close();
    return 0;
}
