#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<iomanip>
#include<cassert>

using namespace std;

const int N = 14000;
const int INF = 1e9 + 47;

namespace DijkstraMT {
    int g[N][N];
    int d[N];
    int best[T];
    bool was[N];
    
    void f1(int l, int r, int ind) {
        int v = -1;
        for (int u = l; u < r; ++u) {
            if (!was[u] && (v == -1 || d[v] > d[u])) {
                v = u;
            }
        }
       best[ind] = v;
    }

    void f2(int l, int r, int v) {
        for (int u = l; u < r; ++u) {
            if (d[u] > g[v][u] + d[v]) {
                d[u] = g[v][u] + d[v];
            }
        }
    }

    void get_dist() {
        for (int i = 0; i < N; ++i) {
            d[i] = INF;
        }
        d[0] = 0;
        for (int i = 0; i < N; ++i)  {
            for (int i = 0; i < T; ++i) {
                best[i] = -1;
            }
            vector<thread> t1(T);
            for (int i = 0; i < T; ++i) {
                int l = i * (N / T);
                int r = (i + 1) * (N / T);
                if (i == T - 1) {
                    r = N;
                }
                t1[i] = thread(f1, l, r, i);
            }
            for (int i = 0; i < T; ++i) {
                t1[i].join();
            }
            
            int v = -1;
            for (int i = 0; i < T; ++i) {
                int u = best[i];
                if (u != -1 && (v == -1 || d[u] < d[v])) {
                    v = u;
                }
            }
            if (v == -1 || d[v] == INF) {
                break;
            }
            was[v] = true;

            vector<thread> t2(T);
            for (int i = 0; i < T; ++i) {
                int l = i * (N / T);
                int r = (i + 1) * (N / T);
                if (i == T - 1) {
                    r = N;
                }
                t2[i] = thread(f2, l, r, v);
            }
            for (int i = 0; i < T; ++i) {
                t2[i].join();
            }
        }
    }
}
