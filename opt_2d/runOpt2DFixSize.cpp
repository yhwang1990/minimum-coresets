#include <vector>
#include <iostream>

#include "IOUtil.hpp"
#include "Point2D.hpp"
#include "OptimalCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 6) {
        cerr << "usage: ./opt <r> <dataset_path> <dirs_path> <valid_path> <output_path>" << endl;
        exit(EXIT_FAILURE);
    }

    int r = stoi(argv[1]);
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

    output_file << "dataset=" << dataset_path << " r=" << r << "\n";

    bool isFound = false;
    double epsMin = 1.0e-4, epsMax = 0.5, eps = (epsMax + epsMin) / 2.0;
    double time[] = {0, 0, 0, 0, 0};

    vector<int> result_idx;
    vector<Point2D> coreset;

    while (!isFound) {
        cout << "eps=" << eps << endl;

        OptimalCoreset opt_2d(eps, points);
        opt_2d.sort_counter_clockwise(time[0]);
        opt_2d.compute_convex_hull(time[1]);
        opt_2d.select_candidates(time[2]);
        opt_2d.construct_graph(time[3]);

        result_idx = opt_2d.compute_result(time[4]);

        if (abs(epsMax - epsMin) < 1.0e-4) {
            isFound = true;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(opt_2d.points[idx]);
        }

        if (result_idx.size() > r) {
            epsMin = eps;
            eps = (epsMin + epsMax) / 2.0;
        } else if (result_idx.size() < r) {
            epsMax = eps;
            eps = (epsMin + epsMax) / 2.0;
        } else {
            isFound = true;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(opt_2d.points[idx]);
        }
    }

    cout << coreset.size() << endl;

    vector<double> regret_dist;
    Validation::loss_distribution(coreset, queries, results, regret_dist);

    for (int regret : regret_dist)
        output_file << regret << "\n";
    output_file.close();

    return 0;
}