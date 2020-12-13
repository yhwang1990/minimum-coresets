#include <vector>
#include <iostream>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "OptimalCoreset.h"
#include "Validation.hpp"

using namespace std;

int main() {

    string dataset_path = "../examples/example.txt";

    vector<Point2D> points;

    IOUtil::read_input_points(dataset_path.c_str(), points);

    double eps = 0.1;
    double time[5];

    cout << "eps=" << eps << endl;

    OptimalCoreset optimalCoreset(eps, points);
    optimalCoreset.sort_counter_clockwise(time[0]);

    for (int i = 0; i < 50; ++i) {
        cout << i << ":" << optimalCoreset.points[i].x << "," << optimalCoreset.points[i].y << endl;
    }
    cout << endl;

    optimalCoreset.compute_convex_hull(time[1]);

    for (int it : optimalCoreset.convex_hull) {
        cout << it << endl;
    }
    cout << endl;

    optimalCoreset.select_candidates(time[2]);

    for (int it : optimalCoreset.candidates) {
        cout << it << endl;
    }
    cout << endl;

    optimalCoreset.construct_graph(time[3]);

    optimalCoreset.G.print();
    cout << endl;

    vector<int> result_idx = optimalCoreset.compute_result(time[4]);

    for (int it : result_idx) {
        cout << it << endl;
    }
    cout << endl;

    return 0;
}