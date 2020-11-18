#include <algorithm>
#include <chrono>

#include "ExactGRMR.h"
#include "IOUtil.hpp"

ExactGRMR::ExactGRMR(double eps, const vector<Point2D> &points) {
    this->eps = eps;
    for (Point2D p : points)
        this->points.push_back(p);
}

void ExactGRMR::sort_counter_clockwise(double &time) {
    auto start = chrono::high_resolution_clock::now();

    sort(points.begin(), points.end());

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

void ExactGRMR::compute_convex_hull(double &time) {
    auto start = chrono::high_resolution_clock::now();
    int n = points.size();

    if (n < 3)
        return;

    int r = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x > points[r].x)
            r = i;
    }

    int p = r, q;
    do {
        convex_hull.insert(p);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 1)
                q = i;
        }
        p = q;
    } while (p != r);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

void ExactGRMR::select_candidates(double &time) {
    auto start = chrono::high_resolution_clock::now();
    int n = points.size(), m = convex_hull.size();

    vector<int> temp_ch;
    temp_ch.reserve(m);
    for (int idx : convex_hull)
        temp_ch.push_back(idx);

    vector<Point2D> dirs;
    dirs.reserve(m);
    for (int i = 0; i < temp_ch.size() - 1; ++i) {
        Point2D dir(points[temp_ch[i + 1]].y - points[temp_ch[i]].y, points[temp_ch[i]].x - points[temp_ch[i + 1]].x);
        dirs[i] = dir;
    }
    Point2D dir(points[temp_ch[0]].y - points[temp_ch[m - 1]].y, points[temp_ch[m - 1]].x - points[temp_ch[0]].x);
    dirs[m - 1] = dir;

    for (int p_idx = 0; p_idx < n; ++p_idx) {
        if (convex_hull.find(p_idx) != convex_hull.end())
            candidates.push_back(p_idx);
        else {
            for (int j = 0; j < m; ++j) {
                if (points[p_idx].dotP(dirs[j]) >= (1 - eps) * points[temp_ch[j]].dotP(dirs[j])) {
                    candidates.push_back(p_idx);
                    break;
                }
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

void ExactGRMR::construct_graph(double &time) {
    auto start = chrono::high_resolution_clock::now();
    int n = candidates.size();
    this->G.add_vertices(candidates);

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        while (true) {
            double weight = edge_weight(candidates[i], candidates[j]);
            if (weight >= 0 && weight <= eps) {
                G.add_edge(candidates[i], candidates[j]);
            } else {
                if (convex_hull.find(candidates[j]) != convex_hull.end())
                    break;
            }
            j = (j + 1) % n;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

void ExactGRMR::fast_construct_graph(double &time) {
    auto start = chrono::high_resolution_clock::now();
    int n = convex_hull.size();
    for (int idx : convex_hull)
        candidates.push_back(idx);
    G.add_vertices(candidates);

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        while (true) {
            double weight = edge_weight(candidates[i], candidates[j]);
            if (weight >= 0 && weight <= eps) {
                this->G.add_edge(candidates[i], candidates[j]);
            } else {
                if (convex_hull.find(candidates[j]) != convex_hull.end())
                    break;
            }
            j = (j + 1) % n;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

vector<int> ExactGRMR::compute_result(double &time) {
    auto start = chrono::high_resolution_clock::now();

    int pivot = *(convex_hull.begin());
    vector<pair<int, int>> pairs;
    for (int idx : G.adj[pivot]) {
        pairs.emplace_back(pivot, idx);
    }

    int min_length = INT_MAX;
    vector<int> min_cycle, cycle;
    bool is_shortest = false;
    for (auto &it : pairs) {
        G.shortest_path(it.second, it.first, cycle);
        if (cycle.size() < min_length) {
            min_length = cycle.size();
            min_cycle = cycle;
        }
        if (min_length <= 4) {
            is_shortest = true;
            break;
        }
    }

    if (is_shortest) {
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        time = duration.count();

        return min_cycle;
    }

    pairs.clear();
    for (auto &it : G.adj) {
        int s = it.first;
        if (s < pivot) {
            for (int t : it.second) {
                if (t > pivot)
                    pairs.emplace_back(s, t);
            }
        } else if (s > pivot) {
            for (int t : it.second) {
                if (t < s && t > pivot)
                    pairs.emplace_back(s, t);
            }
        }
    }

    for (auto &it : pairs) {
        G.shortest_path(it.second, it.first, cycle);
        if (cycle.size() < min_length) {
            min_length = cycle.size();
            min_cycle = cycle;
        }
        if (min_length <= 4)
            break;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();

    return min_cycle;
}

int ExactGRMR::orientation(Point2D p, Point2D q, Point2D r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (abs(val) < 1e-6)
        return 0;
    return (val > 0) ? 1 : 2;
}

double ExactGRMR::edge_weight(int s, int t) {
    double weight = 0.0;
    Point2D dir(points[t].y - points[s].y, points[s].x - points[t].x);
    if (s < t) {
        auto it = convex_hull.lower_bound(s);
        if (*it == s)
            ++it;
        while (*it < t && it != convex_hull.end()) {
            int idx = *it;
            double weight_i = (points[idx].dotP(dir) - points[s].dotP(dir)) / points[idx].dotP(dir);
            assert(weight_i >= 0);
            weight = max(weight, weight_i);
            ++it;
        }
    } else {
        auto it = convex_hull.lower_bound(s);
        if (*it == s)
            ++it;
        while (it != convex_hull.end()) {
            int idx = *it;
            double weight_i = (points[idx].dotP(dir) - points[s].dotP(dir)) / points[idx].dotP(dir);
            assert(weight_i >= 0);
            weight = max(weight, weight_i);
            ++it;
        }

        it = convex_hull.begin();
        while (*it < t) {
            int idx = *it;
            double weight_i = (points[idx].dotP(dir) - points[s].dotP(dir)) / points[idx].dotP(dir);
            assert(weight_i >= 0);
            weight = max(weight, weight_i);
            ++it;
        }
    }
    return weight;
}
