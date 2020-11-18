#include <vector>
#include <climits>

#include "IOUtil.hpp"
#include "Point.hpp"
#include "HeurCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int dim = stoi(argv[1]);
    char *dataset_path = argv[2];
    char *topk_path = argv[3];
    char *query_path = argv[4];
    char *validation_path = argv[5];
    char *output_path = argv[6];

    vector<Point> points, queries;
    vector<double> results;

    IOUtil::read_input_points(dataset_path, dim, points);
    IOUtil::read_input_points(query_path, dim, queries);
    IOUtil::read_validate_results(validation_path, results);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n";
    output_file.flush();

    double params[20] = {0.0};
    if (dim > 2) {
        for (int i = 0; i < 10; ++i)
            params[i] = 0.01 * (i + 1);
    } else {
        double params_2d[11] = {0.0001, 0.0002, 0.0005, 0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2};
        for (int i = 0; i < 11; ++i)
            params[i] = params_2d[i];
    }

    for (double eps : params) {
        if (eps < 0.00001)
            continue;

        cout << "eps=" << eps << endl;

        double t1 = 0.0, t2 = 0.0, t3 = 0.0;
        HeurCoreset heuristicGrmr(eps, points);

        if (dim > 2) {
            heuristicGrmr.construct_IPDG(topk_path, t1);
            heuristicGrmr.construct_graph(t2);
        } else {
            heuristicGrmr.construct_graph_2d(t2);
        }

        double gap_eps;
        if (eps < 0.01)
            gap_eps = 0.0001;
        else
            gap_eps = 0.0005;

        double delta_min = eps, delta_max = 1.0 - heuristicGrmr.MIN_WEIGHT;
        double delta = min(2 * delta_min, delta_max);
        int size = INT_MAX;
        double loss;
        while (true) {
            cout << "delta=" << delta << endl;
            vector<int> result_idx = heuristicGrmr.compute_result(delta, t3);

            vector<Point> coreset;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(heuristicGrmr.extremes[idx]);
            bool is_valid = Validation::validate(eps, coreset, queries, results);

            if (is_valid && delta_max - delta_min < gap_eps) {
                loss = Validation::calc_loss(coreset, queries, results);
                break;
            }

            if (is_valid && size == coreset.size()) {
                loss = Validation::calc_loss(coreset, queries, results);
                break;
            }

            if (!is_valid || size < coreset.size()) {
                delta_max = delta;
                delta = (delta_min + delta_max) / 2.0;
            } else if (size > coreset.size()) {
                delta_min = delta;
                delta = min(2 * delta_min, (delta_min + delta_max) / 2.0);
                size = coreset.size();
            }
        }

        output_file << "eps=" << eps << " loss=" << loss << "\n";
        output_file.flush();
    }
    output_file.close();

    return 0;
}