#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;
struct stamp {
    int num;
    int route;
    int howmany;
    int index;

    stamp() { }

    stamp (int nu, int r, int h, int in)
    {
        num = nu;
        route = r;
        howmany = h;
        index = in;
    }
};

struct Dijkstra {
    stamp stampp;
    long long mindist;
    Dijkstra(stamp n, long long min)
    {
        stampp.num = n.num;
        stampp.route = n.route;
        stampp.howmany = n.howmany;
        stampp.index = n.index;
        mindist = min;
    }
};

long long int k = 2000000000;
int indexxx = -1;
vector<int> path;

void dijkstra(vector< vector<long long int> > distances, vector<stamp> graph, int ii)
{
    vector<Dijkstra> ok;
    Dijkstra dij(graph[0], 0);
    ok.push_back(dij);
    vector<Dijkstra> nok;
    for (int i = 1; i < graph.size(); i++) {
            Dijkstra di(graph[i], 2000000000);
            nok.push_back(di);
    }
    while (ok[ok.size()-1].stampp.num != ii)
    {
        for (int j = 0; j < nok.size(); j++)
            if (nok[j].mindist > ok[ok.size()-1].mindist +
                    distances[ok[ok.size()-1].stampp.index][nok[j].stampp.index])
            {
                nok[j].mindist =  ok[ok.size()-1].mindist +
                    distances[ok[ok.size()-1].stampp.index][nok[j].stampp.index];
                path[nok[j].stampp.index] = ok[ok.size() - 1].stampp.index;
            }
        long long int min = 2100000000;
        stamp sta;
        int index2 = -1;
        for (int i = 0; i < nok.size(); i++)
        {
            if (nok[i].mindist < min)
            {
                min = nok[i].mindist;
                sta.index = nok[i].stampp.index;
                sta.num = nok[i].stampp.num;
                sta.howmany = nok[i].stampp.howmany;
                sta.route = nok[i].stampp.route;
                index2 = i;
            }
        }
        Dijkstra d(sta, min);
        ok.push_back(d);
        nok.erase(nok.begin()+index2);
    }
    k = ok[ok.size()-1].mindist;
    indexxx = ok[ok.size()-1].stampp.index;
}

using namespace std;

int main() {
    ifstream fin("in.txt");
    int n;
    fin >> n;
    int r;
    fin >> r;
    int I;
    fin >> I;
    int J;
    fin >> J;
    int m;
    int gSize = 1;
    vector<int> sizes;
    vector<stamp> graph;
    stamp sst(-1,-1,-1,0);
    graph.push_back(sst);
    vector< vector<long long int> > distances;
    int cons = 1;
    for (int i = 0; i < r; i++)
    {
        fin >> m;
        sizes.push_back(m);
        gSize += m;
        for (int j = 0; j < m; j++)
        {
            int t;
            fin >> t;
            stamp st(t,i,j, cons);
            graph.push_back(st);
            cons++;
        }
    }
    fin.close();
    vector<long long int> distan;
    for (int i = 0; i < gSize; i++)
    {
        for (int j = 0; j < gSize; j++)
        {
            if (graph[i].num == -1)
            {
                if (graph[j].num == J)
                {
                    distan.push_back(0);
                }
                else
                {
                    distan.push_back(2000000000);
                }
            }
            else if (graph[j].num == -1)
            {
                if (graph[i].num == J)
                {
                    distan.push_back(0);
                }
                else
                {
                    distan.push_back(2000000000);
                }
            }

            else if (i ==j)
            {
                distan.push_back(2000000000);
            }
            else if (graph[i].num == graph[j].num && graph[i].route != graph[j].route)
            {
                distan.push_back(3);
            }
            else if (graph[i].num == graph[j].num && graph[i].route == graph[j].route && abs(graph[i].howmany - graph[j].howmany) > 1)
            {
                distan.push_back(3);
            }
            else if (graph[i].route == graph[j].route && abs(graph[i].howmany - graph[j].howmany) == 1)
            {
                distan.push_back(1);
            }
            else
            {
                distan.push_back(2000000000);
            }
        }
        distances.push_back(distan);
        distan.clear();
    }
    for (int i = 0; i < graph.size(); i++)
        path.push_back(-1);
    vector <stamp> is;
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].num == I)
            is.push_back(graph[i]);
    }
    ofstream fout("out.txt");
    if (is.size() == 0)
    {
        fout << "NoWay";
        fout.close();
        return 0;
    }
    dijkstra(distances, graph, I);
    for (int i = 0; i < distances.size(); i++)
    {
        for (int j = 0; j < distances[i].size(); j++)
        {
            cout << distances[i][j] << setw(11) << " ";
        }
        cout << endl;
    }
    cout << k << endl;
    if (I == J)
    {
        fout << 0 << '\n';
        fout.close();
    }
    if (k == 2000000000)
    {
        fout << "NoWay";
        fout.close();
        return 0;
    }
    vector<stamp> myWay;
    while (path[indexxx] != -1)
    {
        myWay.push_back(graph[indexxx]);
        indexxx = path[indexxx];
    }
    vector<int> path;
    fout << k << '\n';
    for (int i = myWay.size()-1; i > -1; i--)
    {
        if (myWay[i].num != myWay[i-1].num)
            fout <<"StopNo " << myWay[i].num << " BusNo " << myWay[i].route+1 << '\n';
    }
    fout.close();
    return 0;
}