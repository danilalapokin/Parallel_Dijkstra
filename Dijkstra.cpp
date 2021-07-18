#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<iomanip>
#include<cassert>

using namespace std;

const int N = 14000;
const int INF = 1e9 + 47;

struct Dijkstra {
    int g[N][N];
    int d[N];
    bool was[N];

    void get_dist() {
        for (int i = 0; i < N; ++i) {
            d[i] = INF;
        }
        d[0] = 0;
        for (int i = 0; i < N; ++i) {
            int v = -1;
            for (int u = 0; u < N; ++u) {
                if (!was[u] && (v == -1 || d[v] > d[u])) {
                    v = u;
                }
            }
            if (v == -1 || d[v] == INF) {
                break;
            }
            was[v] = true;

            for (int u = 0; u < N; ++u) {
                if (d[v] + g[v][u] < d[u]) {
                    d[u] = g[v][u] + d[v];
                }
            }
        }
    }
}

