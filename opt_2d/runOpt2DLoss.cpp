#include <vector>
#include <iostream>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "OptimalCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    char *dataset_path = argv[1];
    char *output_path = argv[2];
    char *query_path = argv[3];
    char *valid_path = argv[4];

    vector<Point2D> points, queries;
    vector<double> results;

    IOUtil::read_input_points(dataset_path, points);
    IOUtil::read_input_points(query_path, queries);
    IOUtil::read_validate_results(valid_path, results);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n" << endl;

    double params[] = {0.0001, 0.0002, 0.0005, 0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2};
    double time[] = {0, 0, 0, 0};

    for (double eps : params) {
        cout << "eps=" << eps << endl;

        OptimalCoreset exactGrmr(eps, points);
        exactGrmr.sort_counter_clockwise(time[0]);
        exactGrmr.compute_convex_hull(time[1]);
        exactGrmr.fast_construct_graph(time[2]);
        vector<int> result_idx = exactGrmr.compute_result(time[3]);

        vector<Point2D> epsKernel;
        epsKernel.reserve(result_idx.size());
        for (int idx : result_idx)
            epsKernel.push_back(exactGrmr.points[idx]);

        double loss = Validation::calc_loss(epsKernel, queries, results);

        output_file << "eps=" << eps << " loss=" << loss << "\n" << flush;
    }
    output_file.close();

    return 0;
}