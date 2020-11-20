#include <vector>

#include "IOUtil.hpp"
#include "Point.hpp"
#include "HeurCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int mode = stoi(argv[1]);
    int dim = stoi(argv[2]);
    double eps = stod(argv[3]);

    char *dataset_path = argv[4];
    char *graph_path = argv[5];
    char *dirs_path = argv[6];
    char *validation_path = argv[7];
    char *output_path = argv[8];

    vector<Point> points, queries;
    vector<double> results;

    IOUtil::read_input_points(dataset_path, dim, points);
    IOUtil::read_input_points(dirs_path, dim, queries);
    IOUtil::read_validate_results(validation_path, results);

    ofstream output_file;
    output_file.open(output_path, ofstream::out | ofstream::app);

    HeurCoreset heurMD(points);

    double t1 = 0.0, t2 = 0.0, t3 = 0.0;

    if (mode == 0) {
        if (dim > 2) {
            heurMD.read_IPDG(graph_path);
            heurMD.construct_graph(t2);
        } else {
            heurMD.construct_graph_2d(t2);
        }

    } else {
        output_file << "dataset=" << dataset_path << "\n";
        output_file.flush();

        cout << "eps=" << eps << endl;

        double query_time = 0.0;
        int size = -1;

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