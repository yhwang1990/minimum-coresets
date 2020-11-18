#ifndef EXACT_GRMR_H
#define EXACT_GRMR_H

#include <cassert>
#include <set>
#include <vector>

#include "Digraph.hpp"
#include "Point2D.hpp"

using namespace std;

class ExactGRMR {
public:
    double eps;
    vector<Point2D> points;
    set<int> convex_hull;
    vector<int> candidates;
    Digraph G;

    ExactGRMR(double eps, const vector<Point2D> &points);

    void sort_counter_clockwise(double &time);

    void compute_convex_hull(double &time);

    void select_candidates(double &time);

    void construct_graph(double &time);

    void fast_construct_graph(double &time);

    vector<int> compute_result(double &time);

private:
    static int orientation(Point2D p, Point2D q, Point2D r);

    double edge_weight(int s, int t);
};

#endif // EXACT_GRMR_H
