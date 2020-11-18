#ifndef DOMINANCE_GRAPH_HPP
#define DOMINANCE_GRAPH_HPP

#include <cmath>
#include <climits>
#include <iostream>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class DominanceGraph {

public:
    vector<vector<pair<int, double>>> adj;

    DominanceGraph() = default;

    void add_vertices(int N) {
        this->adj.reserve(N);
        for (int u = 0; u < N; ++u) {
            vector<pair<int, double>> u_adj;
            adj.push_back(u_adj);
        }
    }

    void add_edge(int u, int v, double weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    void subgraph(double eps, vector<unordered_set<int>> &sets) {
        sets.clear();
        for (int i = 0; i < adj.size(); ++i) {
            unordered_set<int> u_set;
            u_set.insert(i);
            for (auto &edge : adj[i]) {
                if (edge.second >= 1.0 - eps) {
                    u_set.insert(edge.first);
                }
            }
            sets.push_back(u_set);
        }
    }

    void print() {
        for (int i = 0; i < adj.size(); i++) {
            for (auto &item : adj[i]) {
                cout << i << "->" << item.first << ":" << item.second << endl;
            }
            cout << endl;
        }
    }

};

#endif //DOMINANCE_GRAPH_HPP
