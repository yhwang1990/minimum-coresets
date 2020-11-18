#ifndef HEURISTIC_GRMR_H
#define HEURISTIC_GRMR_H

#include <vector>

#include "DelaunayGraph.hpp"
#include "DominanceGraph.hpp"

#include "Point.hpp"

using namespace std;

class HeuristicGRMR {
public:
    int dim, N;
    double MIN_WEIGHT;
    vector<Point> extremes;
    DelaunayGraph IPDG;
    DominanceGraph G;

    HeuristicGRMR(double eps, const vector<Point> &extremes);

    void construct_IPDG(const char *filename, double &time);

    void construct_graph(double &time);

    void construct_graph_2d(double &time);

    vector<int> compute_result(double delta, double &time);

    double edge_weight(int i, int j);

    double edge_weight_2d(int i, int j);
};

#endif // HEURISTIC_GRMR_H
