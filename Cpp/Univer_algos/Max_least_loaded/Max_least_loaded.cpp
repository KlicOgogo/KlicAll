#include <vector>
#include <algorithm>
#include <fstream>

int main() {
    std::ifstream fin("input.txt");
    int m, n;
    fin >> n >> m;
    std::vector<long long int> jobs(n);
    for (int i = 0; i < n; i++) {
        fin >> jobs[i];
    }
    fin.close();
    std::vector<long long int> workers(m);
    std::sort(jobs.begin(), jobs.end());
    for (int i = jobs.size()-1; i > -1; i--) {
        long long int j = std::min_element(workers.begin(), workers.end()) - workers.begin();
        workers[j] += jobs[i];
    }
    std::ofstream fout("output.txt");
    fout << *(std::min_element(workers.begin(), workers.end()));
    fout.close();
    return 0;
}
