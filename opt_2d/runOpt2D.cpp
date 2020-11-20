#include <vector>
#include <iostream>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "OptimalCoreset.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cerr << "usage: ./opt <dataset_path> <output_path>" << endl;
        exit(EXIT_FAILURE);
    }


    char *dataset_path = argv[1];
    char *output_path = argv[2];

    vector<Point2D> points;

    IOUtil::read_input_points(dataset_path, points);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n";

    double params[] = {0.001, 0.0025, 0.005, 0.01, 0.025, 0.05, 0.1, 0.15, 0.2, 0.25};
    double time[] = {0, 0, 0, 0, 0};

    for (double eps : params) {
        cout << "eps=" << eps << endl;

        OptimalCoreset opt_2d(eps, points);
        opt_2d.sort_counter_clockwise(time[0]);
        opt_2d.compute_convex_hull(time[1]);
        opt_2d.select_candidates(time[2]);
        opt_2d.fast_construct_graph(time[3]);

        vector<int> result_idx = opt_2d.compute_result(time[4]);

        double total_time = 0.0;
        for (int i = 2; i < 5; i++)
            total_time += time[i];

        output_file << "eps=" << eps << " size=" << result_idx.size();
        output_file << " time=" << total_time / 1000.0 << " sc_time=" << time[2] / 1000.0
                    << " cg_time=" << time[3] / 1000.0 << " result_time=" << time[4] / 1000.0 << "\n" << flush;
    }

    output_file.close();

    return 0;
}