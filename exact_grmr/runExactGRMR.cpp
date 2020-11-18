#include <vector>
#include <iostream>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "ExactGRMR.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    char *dataset_path = argv[1];
    char *output_path = argv[2];

    vector<Point2D> points;

    IOUtil::read_input_points(dataset_path, points);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n";

    double params[] = {0.0001, 0.0005, 0.001, 0.005, 0.01, 0.05, 0.1};
    double time[] = {0, 0, 0, 0, 0};

    for (double eps : params) {
        cout << "eps=" << eps << endl;

        ExactGRMR exactGrmr(eps, points);
        exactGrmr.sort_counter_clockwise(time[0]);
        exactGrmr.compute_convex_hull(time[1]);
        exactGrmr.select_candidates(time[2]);
        exactGrmr.construct_graph(time[3]);

        vector<int> result_idx = exactGrmr.compute_result(time[4]);

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