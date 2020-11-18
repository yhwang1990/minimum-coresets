#ifndef DELAUNAY_GRAPH_HPP
#define DELAUNAY_GRAPH_HPP

#include <cmath>
#include <climits>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class DelaunayGraph {

public:
    vector<set<int>> edges;

    DelaunayGraph() = default;

    DelaunayGraph(DelaunayGraph const &g) {
        this->edges.reserve(g.edges.size());
        for (int v = 0; v < this->edges.size(); ++v) {
            set<int> v_edge;
            this->edges.push_back(v_edge);
        }

        for (int u = 0; u < g.edges.size(); ++u) {
            for (int v : g.edges[u])
                this->add_edge(u, v);
        }
    }

    void add_vertices(int N) {
        edges.reserve(N);
        for (int v = 0; v < N; ++v) {
            set<int> v_edge;
            edges.push_back(v_edge);
        }
    }

    void add_edge(int u, int v) {
        edges[u].insert(v);
        edges[v].insert(u);
    }

    void print() {
        for (int i = 0; i < edges.size(); i++) {
            for (int j : edges[i]) {
                cout << i << "-" << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

};

#endif //DELAUNAY_GRAPH_HPP
