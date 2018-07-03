#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

struct Point {
    int x, y;
    Point(int x_, int y_): x(x_), y(y_) {}
    std::string to_string() {
        return "("+ std::to_string(x) +";"+ std::to_string(y) +")";
    }
};

struct Line {
    double a, b, c;
    Line(double a_, double b_, double c_): a(a_), b(b_), c(c_) {}
    void divOnNumber(double number) {
        if (number != 0) {
            a /= number;
            b /= number;
            c /= number;
        }
    }
    void addLineOnNumber(double number, Line line) {
        a += number * line.a;
        b += number * line.b;
        c += number * line.c;
    }
};

struct Dijkstra {
    int n;
    double minD;
    Dijkstra() = default;
    Dijkstra(int n_, double minD_): n(n_), minD(minD_) {}
};

double gaussian(Line l1, Line l2, Point house, Point p1, Point p2) {
    if (l1.a * l2.b - l2.a * l1.b == 0) {
        if (l1.b * l2.c - l2.b * l1.c == 0) {
            if (house.x < std::max(p1.x, p2.x) &&
                house.x > std::min(p1.x, p2.x) - 5) {
                return house.x + 1;
            } else {
                return -6;
            }
        } else {
            return -6;
        }
    } else {
        return (l1.c * l2.b - l1.b * l2.c) / (l1.a * l2.b - l2.a * l1.b);
    }
}

bool intersects (Point p1, Point p2, Point house) {
    double inter1 = gaussian(Line(p2.y - p1.y, p1.x - p2.x, p1.x * p2.y - p1.y * p2.x),
                             Line(-1, 1, house.y - house.x), house, p1, p2);
    if (inter1 > house.x && inter1 < house.x + 5 &&
        inter1 > std::min(p1.x, p2.x) && inter1 < std::max(p1.x, p2.x)) {
        return true;
    }
    double inter2 = gaussian(Line(p2.y - p1.y, p1.x - p2.x, p1.x * p2.y - p1.y * p2.x),
                             Line(1, 1, house.x + house.y + 5), house, p1, p2);
    return inter2 > house.x && inter2 < house.x + 5 &&
    inter2 > std::min(p1.x, p2.x) && inter2 < std::max(p1.x, p2.x);
}

bool intersectsAll (Point p1, Point p2, const std::vector<Point> &houses) {
    for (auto house : houses) {
        if (intersects(p1, p2, house)) {
            return true;
        }
    }
    return false;
}

double dijkstra(const std::vector<std::vector<double>> &dist, size_t dim, std::vector<int> &path) {
    std::vector<Dijkstra> ok;
    ok.emplace_back(0, 0);
    std::vector<Dijkstra> nok(dim-1);
    for (int i = 1; i < dim; ++i) {
        nok[i-1] = Dijkstra(i, 2000000000);
    }
    for (int y = 0; y < dim-1; ++y) {
        for (auto i : nok) {
            if (i.minD > ok.back().minD + dist[ok.back().n][i.n]) {
                i.minD = ok.back().minD + dist[ok.back().n][i.n];
                path[i.n] = ok.back().n;
            }
        }
        double min = 2100000000;
        int ind1 = -1, ind2 = -1;
        for (int i = 0; i < nok.size(); ++i) {
            if (nok[i].minD < min) {
                min = nok[i].minD;
                ind1 = nok[i].n;
                ind2 = i;
            }
        }
        ok.emplace_back(Dijkstra(ind1, min));
        nok.erase(nok.begin() + ind2);
    }
    for (auto i : ok) {
        if (i.n == dim-1) {
            return i.minD;
        }
    }
}

int main() {
    std::ifstream in("input.in");
    size_t n;
    in >> n;
    std::vector<Point> points, houses;
    points.emplace_back(Point(0,0));
    int x, y;
    for (int i = 0; i < n; ++i) {
        in >> x >> y;
        points.emplace_back(Point(x, y));
        houses.emplace_back(Point(x, y));
        points.emplace_back(Point(x+5, y));
        points.emplace_back(Point(x, y+5));
        points.emplace_back(Point(x+5, y+5));
    }
    in.close();
    points.emplace_back(Point(100, 100));
    size_t l = 4 * n + 2;
    std::vector<std::vector<int>> matrix(l, std::vector<int>(l));
    std::vector<std::vector<double>> dist(l, std::vector<double>(l));
    for (int i = 0 ; i < l; ++i) {
        for (int j = 0; j < l; ++j) {
            if (i == j) {
                dist[i][j] = 2000000000;
            } else {
                if (intersectsAll(points[i], points[j], houses)) {
                    dist[i][j] = 2000000000;
                } else {
                    matrix[i][j] = 1;
                    dist[i][j] = std::sqrt(std::pow(points[i].x - points[j].x, 2) +
                                           std::pow(points[i].y - points[j].y, 2));
                }
            }
        }
    }
    std::ofstream of("output.out");
    std::vector<int> path(l, -1);
    auto min_dist = dijkstra(dist, l, path);
    int t = static_cast<int>(min_dist * 100);
    double ans;
    if (t % 10 <= 4) {
        t -= t % 10;
    } else {
        t += 10 - t % 10;
    }
    ans = static_cast<double>(t) / 100;
    of << ans << '\n';
    int i = l-1;
    std::vector<Point> result;
    result.emplace_back(Point(100, 100));
    while (path[i] != -1) {
        result.emplace_back(points[path[i]]);
        i = path[i];
    }
    for (int j = result.size()-1; j > -1; j--) {
        of << result[i].to_string() << ' ';
    }
    of.close();
    return 0;
}