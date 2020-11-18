#include <vector>

#include "IOUtil.hpp"
#include "Point.hpp"
#include "HeuristicGRMR.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int dim = stoi(argv[1]);
    char *dataset_path = argv[2];
    char *topk_path = argv[3];
    char *dirs_path = argv[4];
    char *validation_path = argv[5];
    char *output_path = argv[6];
    int all = stoi(argv[7]);

    vector<Point> points, queries;
    vector<double> results;

    IOUtil::read_input_points(dataset_path, dim, points);
    IOUtil::read_input_points(dirs_path, dim, queries);
    IOUtil::read_validate_results(validation_path, results);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n";
    output_file.flush();

    double params[10];
    if (all == 1) {
        for (int i = 0; i < 10; ++i)
            params[i] = 0.01 * (i + 1);
    } else if (all == 0) {
        for (int i = 0; i < 2; ++i)
            params[i] = 0.05 * (i + 1);
        for (int i = 2; i < 10; ++i)
            params[i] = 0.0;
    } else {
        double params_2d[10] = {0.0001, 0.0005, 0.001, 0.005, 0.01, 0.05, 0.1, 0.0, 0.0, 0.0};
        for (int i = 0; i < 10; ++i)
            params[i] = params_2d[i];
    }

    for (double eps : params) {
        if (eps < 0.00001)
            continue;

        cout << "eps=" << eps << endl;

        double t1 = 0.0, t2 = 0.0, t3 = 0.0;
        double query_time = 0.0;
        int size = -1;

        HeuristicGRMR heuristicGrmr(eps, points);

        if (dim > 2) {
            heuristicGrmr.construct_IPDG(topk_path, t1);
            heuristicGrmr.construct_graph(t2);
        } else {
            heuristicGrmr.construct_graph_2d(t2);
        }

        double delta_min = eps, delta_max = 1.0 - heuristicGrmr.MIN_WEIGHT;
        double delta = min(2 * delta_min, delta_max);

        while (true) {
            cout << "delta=" << delta << endl;
            vector<int> result_idx = heuristicGrmr.compute_result(delta, t3);
            query_time += t3;

            vector<Point> coreset;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(heuristicGrmr.extremes[idx]);
            bool is_valid = Validation::validate(eps, coreset, queries, results);

            if (is_valid && size > 0 && delta_max - delta_min < 0.0005)
                break;

            if (is_valid && size == coreset.size())
                break;

            if (!is_valid || size < coreset.size()) {
                delta_max = delta;
                delta = (delta_min + delta_max) / 2.0;
            } else if (size < 0 || size > coreset.size()) {
                delta_min = delta;
                delta = min(2 * delta_min, (delta_min + delta_max) / 2.0);
                size = coreset.size();
            }
        }

        output_file << "eps=" << eps << " time=" << (t1 + t2 + query_time) / 1000.0
                    << " build-graph=" << (t1 + t2) / 1000.0 << " query=" << query_time / 1000.0
                    << " size=" << size << "\n";
        output_file.flush();
    }
    output_file.close();

    return 0;
}