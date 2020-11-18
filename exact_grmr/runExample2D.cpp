#include <vector>
#include <iostream>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "ExactGRMR.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    string dataset_path = "../examples/example.txt";

    vector<Point2D> points;

    IOUtil::read_input_points(dataset_path.c_str(), points);

    double eps = 0.1;
    double time[5];

    cout << "eps=" << eps << endl;

    ExactGRMR exactGrmr(eps, points);
    exactGrmr.sort_counter_clockwise(time[0]);

    for (int i = 0; i < 50; ++i) {
        cout << i << ":" << exactGrmr.points[i].x << "," << exactGrmr.points[i].y << endl;
    }
    cout << endl;

    exactGrmr.compute_convex_hull(time[1]);

    for (int it : exactGrmr.convex_hull) {
        cout << it << endl;
    }
    cout << endl;

    exactGrmr.select_candidates(time[2]);

    for (int it : exactGrmr.candidates) {
        cout << it << endl;
    }
    cout << endl;

    exactGrmr.construct_graph(time[3]);

    exactGrmr.G.print();
    cout << endl;

    vector<int> result_idx = exactGrmr.compute_result(time[4]);

    for (int it : result_idx) {
        cout << it << endl;
    }
    cout << endl;

    return 0;
}