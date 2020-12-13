#include <vector>

#include "IOUtil.hpp"
#include "Point.hpp"
#include "HeurCoreset.h"
#include "Validation.hpp"

using namespace std;

int main() {

    string dataset_path = "../examples/example_ex.txt";

    vector<Point> points;
    vector<double> results;

    IOUtil::read_input_points(dataset_path.c_str(), 2, points);

    double t2 = 0.0;
    HeurCoreset heurCoreset(points);
    heurCoreset.construct_graph_2d(t2);
    heurCoreset.G.print();

    return 0;
}