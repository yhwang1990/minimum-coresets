#include <vector>
#include <iostream>
#include <cstring>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "OptimalCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 6) {
        cerr << "usage: ./opt <full> <dataset_path> <dirs_path> <valid_path> <output_path>" << endl;
        exit(EXIT_FAILURE);
    }

    int isFull = stoi(argv[1]);

    char *dataset_path = argv[2];
    char *dirs_path = argv[3];
    char *valid_path = argv[4];
    char *output_path = argv[5];

    vector<Point2D> points, queries;
    vector<double> results;

    IOUtil::read_input_points(dataset_path, points);
    IOUtil::read_input_points(dirs_path, queries);
    IOUtil::read_validate_results(valid_path, results);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n";

    double time[] = {0, 0, 0, 0, 0};
    if (isFull > 0) {
        double params[] = {0.001, 0.0025, 0.005, 0.01, 0.025, 0.05, 0.1, 0.15, 0.2, 0.25};

        for (double eps : params) {
            cout << "eps=" << eps << endl;

            OptimalCoreset opt_2d(eps, points);
            opt_2d.sort_counter_clockwise(time[0]);

            if (strstr(dataset_path, "FourSquare") != nullptr) {
                opt_2d.compute_convex_hull2(time[1]);
            } else {
                opt_2d.compute_convex_hull(time[1]);
            }

            opt_2d.select_candidates(time[2]);

            if (strstr(dataset_path, "FourSquare") != nullptr) {
                opt_2d.fast_construct_graph(time[3]);
            } else {
                opt_2d.construct_graph(time[3]);
            }

            vector<int> result_idx = opt_2d.compute_result(time[4]);

            vector<Point2D> coreset;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(opt_2d.points[idx]);
            bool is_valid = Validation::validate(eps, coreset, queries, results);

            if (!is_valid) {
                exit(EXIT_FAILURE);
            }

            double total_time = 0.0;
            for (int i = 2; i < 5; i++)
                total_time += time[i];

            output_file << "eps=" << eps << " size=" << result_idx.size();
            output_file << " time=" << total_time / 1000.0 << " sc_time=" << time[2] / 1000.0 << " cg_time="
                        << time[3] / 1000.0 << " result_time=" << time[4] / 1000.0 << "\n" << flush;
        }
    } else {
        cout << "eps=" << 0.1 << endl;

        OptimalCoreset opt_2d(0.1, points);
        opt_2d.sort_counter_clockwise(time[0]);
        opt_2d.compute_convex_hull(time[1]);
        opt_2d.select_candidates(time[2]);
        opt_2d.construct_graph(time[3]);

        vector<int> result_idx = opt_2d.compute_result(time[4]);

        vector<Point2D> coreset;
        coreset.reserve(result_idx.size());
        for (int idx : result_idx)
            coreset.push_back(opt_2d.points[idx]);
        bool is_valid = Validation::validate(0.1, coreset, queries, results);

        if (!is_valid) {
            exit(EXIT_FAILURE);
        }

        double total_time = 0.0;
        for (int i = 2; i < 5; i++)
            total_time += time[i];

        output_file << "eps=" << 0.1 << " size=" << result_idx.size();
        output_file << " time=" << total_time / 1000.0 << " sc_time=" << time[2] / 1000.0 << " cg_time="
                    << time[3] / 1000.0 << " result_time=" << time[4] / 1000.0 << "\n" << flush;
    }

    output_file.close();

    return 0;
}