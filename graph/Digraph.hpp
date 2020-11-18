#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <cmath>
#include <climits>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class Digraph {

public:
    set<int> vertices;
    map<int, set<int>> adj;

    Digraph() = default;

    void add_vertices(vector<int> &vertex_list) {
        for (int u : vertex_list) {
            vertices.insert(u);
            set<int> u_adj;
            adj.insert(make_pair(u, u_adj));
        }
    }

    void add_edge(int u, int v) {
        if (adj.find(u) == adj.end() || adj.find(v) == adj.end())
            return;
        else {
            adj[u].insert(v);
        }
    }

    bool BFS(int src, int dest, map<int, int> &dist, map<int, int> &pred) {
        list<int> queue;

        map<int, bool> visited;

        for (int u : vertices) {
            visited.insert(make_pair(u, false));
            dist.insert(make_pair(u, INT_MAX));
            pred.insert(make_pair(u, -1));
        }

        visited[src] = true;
        dist[src] = 0;
        queue.push_back(src);

        while (!queue.empty()) {
            int u = queue.front();
            queue.pop_front();
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    dist[v] = dist[u] + 1;
                    pred[v] = u;
                    queue.push_back(v);

                    if (v == dest)
                        return true;
                }
            }
        }

        return false;
    }

    void shortest_path(int src, int dest, vector<int> &path) {
        map<int, int> dist;
        map<int, int> pred;

        path.clear();

        if (!BFS(src, dest, dist, pred)) {
            cerr << "Not Connected" << endl;
            vector<int> null_path;
            return;
        }
        int pre = dest;
        path.push_back(pre);

        while (pred[pre] != -1) {
            path.push_back(pred[pre]);
            pre = pred[pre];
        }
    }

    void print() {
        for (auto &it : this->adj) {
            int from = it.first;
            for (int to : it.second) {
                cout << from << "->" << to << " ";
            }
            cout << endl;
        }
    }

};

#endif // DIGRAPH_HPP
