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
    char *query_path = argv[4];
    char *validation_path = argv[5];
    char *output_path = argv[6];
    int r = stoi(argv[7]);

    vector<Point> points, queries;
    vector<double> results;

    IOUtil::read_input_points(dataset_path, dim, points);
    IOUtil::read_input_points(query_path, dim, queries);
    IOUtil::read_validate_results(validation_path, results);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    output_file << "dataset=" << dataset_path << "\n";
    output_file.flush();

    double eps = 0.2;
    cout << "eps=" << eps << endl;

    double t1 = 0.0, t2 = 0.0, t3 = 0.0;
    HeuristicGRMR heuristicGrmr(eps, points);

    heuristicGrmr.construct_IPDG(topk_path, t1);
    heuristicGrmr.construct_graph(t2);

    double delta_min = 0, delta_max = 1.0 - heuristicGrmr.MIN_WEIGHT;
    double delta = eps;

    while (true) {
        cout << "delta=" << delta << endl;
        vector<int> result_idx = heuristicGrmr.compute_result(delta, t3);

        if (result_idx.size() == r || (result_idx.size() < r && delta_max - delta_min <= 0.001)) {
            vector<Point> coreset;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(heuristicGrmr.extremes[idx]);

            vector<double> regret_ratios;
            vector<double> regret_values;
            Validation::loss_distribution(coreset, queries, results, regret_ratios, regret_values);

            for (int i = 0; i < queries.size(); ++i)
                output_file << regret_ratios[i] << "," << regret_values[i] << "\n";
            break;
        } else if (result_idx.size() > r) {
            delta_min = delta;
            delta = (delta_min + delta_max) / 2.0;
        } else if (result_idx.size() < r && delta_max - delta_min > 0.001) {
            delta_max = delta;
            delta = (delta_min + delta_max) / 2.0;
        }
    }
    output_file.close();

    return 0;
}