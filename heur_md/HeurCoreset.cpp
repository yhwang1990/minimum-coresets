#include <algorithm>
#include <chrono>
#include <climits>
#include <list>
#include <glpk.h>

#include "IOUtil.hpp"
#include "HeurCoreset.h"
#include "SetCover.hpp"

HeurCoreset::HeurCoreset(const vector<Point> &extremes) {
    for (const Point &p : extremes)
        this->extremes.push_back(p);
    this->dim = this->extremes[0].get_dimension();

    if (this->dim == 2)
        sort(this->extremes.begin(), this->extremes.end());

    this->N = this->extremes.size();
    this->MIN_WEIGHT = 1e-4;

    this->IPDG.add_vertices(this->N);
    this->G.add_vertices(this->N);
}

void HeurCoreset::read_IPDG(const char *filename) {
    vector<pair<int, int>> edges;
    IOUtil::read_IPDG(filename, edges);
    for (auto &item : edges)
        IPDG.add_edge(item.first, item.second);
}

void HeurCoreset::construct_graph(double &time) {
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        list<int> queue;
        vector<bool> visited(N, false);
        visited[i] = true;
        for (int j : IPDG.edges[i])
            queue.push_back(j);

        while (!queue.empty()) {
            int j = queue.front();
            queue.pop_front();
            if (!visited[j]) {
                visited[j] = true;
                double w = edge_weight(i, j);
                if (w >= MIN_WEIGHT) {
                    G.add_edge(i, j, w);
                    for (int k : IPDG.edges[j]) {
                        if (!visited[k])
                            queue.push_back(k);
                    }
                }
            }
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

void HeurCoreset::construct_graph_2d(double &time) {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        while (true) {
            double w = edge_weight_2d(i, j);
            if (w >= MIN_WEIGHT) {
                G.add_edge(i, j, w);
                j = (j + 1) % N;
            } else {
                break;
            }
        }

        j = (i + N - 1) % N;
        while (true) {
            double w = edge_weight_2d(i, j);
            if (w >= MIN_WEIGHT) {
                G.add_edge(i, j, w);
                j = (j + N - 1) % N;
            } else {
                break;
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();
}

void HeurCoreset::write_G(const char *filename) const {
    IOUtil::write_dominance_graph(filename, this->G);
}

void HeurCoreset::read_G(const char *filename) {
    IOUtil::read_dominance_graph(filename, this->G);
}

vector<int> HeurCoreset::compute_result(double delta, double &time) {
    auto start = chrono::high_resolution_clock::now();

    vector<unordered_set<int>> sets;
    G.subgraph(delta, sets);

    vector<int> cov;
    SetCover::get_min_cover_greedy(N, sets, cov);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    time = duration.count();

    return cov;
}

double HeurCoreset::edge_weight(int i, int j) {
    int num_var = dim;
    int num_cons = (int) IPDG.edges[j].size() + 1;

    int ia[1 + num_var * num_cons], ja[1 + num_var * num_cons];
    double ar[1 + num_var * num_cons], z;

    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "edge_weight");
    glp_set_obj_dir(lp, GLP_MIN);
    glp_term_out(GLP_OFF);

    glp_add_rows(lp, num_cons);
    glp_set_row_name(lp, 1, nullptr);
    glp_set_row_bnds(lp, 1, GLP_FX, 1.0, 1.0);
    for (int row = 2; row <= num_cons; ++row) {
        glp_set_row_name(lp, row, nullptr);
        glp_set_row_bnds(lp, row, GLP_LO, 0.0, INT_MAX);
    }

    glp_add_cols(lp, num_var);
    for (int col = 1; col <= num_var; ++col) {
        glp_set_col_name(lp, col, nullptr);
        glp_set_col_bnds(lp, col, GLP_FR, INT_MIN, INT_MAX);
        glp_set_obj_coef(lp, col, extremes[i].get_coordinate(col - 1));
    }

    int row = 1;
    for (int col = 1; col <= num_var; ++col) {
        int idx = col + (row - 1) * num_var;
        ia[idx] = row, ja[idx] = col, ar[idx] = extremes[j].get_coordinate(col - 1);
    }

    auto it = IPDG.edges[j].begin();
    for (row = 2; row <= num_cons; ++row) {
        int p_idx = *it;
        for (int col = 1; col <= num_var; ++col) {
            int idx = col + (row - 1) * num_var;
            double j1 = extremes[j].get_coordinate(col - 1);
            double j2 = extremes[p_idx].get_coordinate(col - 1);
            ia[idx] = row, ja[idx] = col, ar[idx] = (j1 - j2);
        }
        ++it;
    }
    glp_load_matrix(lp, num_var * num_cons, ia, ja, ar);
    glp_simplex(lp, nullptr);

    if (glp_get_status(lp) == GLP_OPT)
        z = glp_get_obj_val(lp);
    else
        z = 0.0;

    glp_delete_prob(lp);
    glp_free_env();

    return z;
}

double HeurCoreset::edge_weight_2d(int i, int j) {
    int ia[7], ja[7];
    double ar[7], z;

    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "edge_weight");
    glp_set_obj_dir(lp, GLP_MIN);
    glp_term_out(GLP_OFF);

    glp_add_rows(lp, 3);
    glp_set_row_name(lp, 1, nullptr);
    glp_set_row_bnds(lp, 1, GLP_FX, 1.0, 1.0);
    glp_set_row_name(lp, 2, nullptr);
    glp_set_row_bnds(lp, 2, GLP_LO, 0.0, INT_MAX);
    glp_set_row_name(lp, 3, nullptr);
    glp_set_row_bnds(lp, 3, GLP_LO, 0.0, INT_MAX);

    glp_add_cols(lp, 2);
    glp_set_col_name(lp, 1, nullptr);
    glp_set_col_bnds(lp, 1, GLP_FR, INT_MIN, INT_MAX);
    glp_set_obj_coef(lp, 1, extremes[i].get_coordinate(0));
    glp_set_col_name(lp, 2, nullptr);
    glp_set_col_bnds(lp, 2, GLP_FR, INT_MIN, INT_MAX);
    glp_set_obj_coef(lp, 2, extremes[i].get_coordinate(1));

    int row = 1;
    for (int col = 1; col <= 2; ++col) {
        int idx = col + (row - 1) * 2;
        ia[idx] = row, ja[idx] = col, ar[idx] = extremes[j].get_coordinate(col - 1);
    }

    for (row = 2; row <= 3; ++row) {
        for (int col = 1; col <= 2; ++col) {
            int idx = col + (row - 1) * 2;
            double j1 = extremes[j].get_coordinate(col - 1);
            double j2;
            if (row == 2)
                j2 = extremes[(j + 1) % N].get_coordinate(col - 1);
            else
                j2 = extremes[(j + N - 1) % N].get_coordinate(col - 1);
            ia[idx] = row, ja[idx] = col, ar[idx] = (j1 - j2);
        }
    }
    glp_load_matrix(lp, 6, ia, ja, ar);
    glp_simplex(lp, nullptr);

    if (glp_get_status(lp) == GLP_OPT)
        z = glp_get_obj_val(lp);
    else
        z = 0.0;

    glp_delete_prob(lp);
    glp_free_env();

    return z;
}
