#include <vector>

#include "IOUtil.hpp"
#include "Point.hpp"
#include "HeurCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 8) {
        cerr << "usage: ./heur <dim> <r> <dataset_path> <graph_path> <dirs_path> <validation_path> <output_path>" << endl;
        exit(EXIT_FAILURE);
    }

    double time = 0.0;

    int dim = stoi(argv[2]);
    int r = stoi(argv[3]);

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

    HeurCoreset heurMD(points);
    heurMD.read_G(graph_path);

    ofstream output_file;
    output_file.open(output_path, ofstream::out | ofstream::app);

    output_file << "dataset=" << dataset_path << " r=" << r;
    output_file.flush();

    double deltaMin = 0, deltaMax = 1, delta = (deltaMin + deltaMax) / 2.0;
    vector<int> result_idx;
    while (true) {
        result_idx = heurMD.compute_result(delta, time);

        cout << "delta=" << delta << " size=" << result_idx.size() << endl;

        if (result_idx.size() > r) {
            deltaMin = delta;
            delta = (deltaMin + deltaMax) / 2.0;
        } else if (result_idx.size() < r) {
            deltaMax = delta;
            delta = (deltaMin + deltaMax) / 2.0;
        } else {
            break;
        }
    }

    vector<Point> coreset;
    coreset.reserve(result_idx.size());
    for (int idx : result_idx)
        coreset.push_back(heurMD.extremes[idx]);

    vector<double> regretDist;
    Validation::loss_distribution(coreset, queries, results, regretDist);

    cout << regretDist[99] << endl;

    for (int i = 0; i < 100; ++i)
        output_file << regretDist[i] << "\n";
    output_file.flush();
    output_file.close();

    return EXIT_SUCCESS;
}