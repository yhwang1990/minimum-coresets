#include <vector>

#include "IOUtil.hpp"
#include "Point.hpp"
#include "HeurCoreset.h"
#include "Validation.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int mode = stoi(argv[1]);

    if (mode == 0 && argc != 6) {
        cerr << "usage: ./heur 0 <dim> <dataset_path> <graph_path> <output_path>" << endl;
        exit(EXIT_FAILURE);
    } else if (mode != 0 && argc != 9) {
        cerr << "usage: ./heur 1 <dim> <eps> <dataset_path> <graph_path> <dirs_path>"
                "<validation_path> <output_path>" << endl;
        exit(EXIT_FAILURE);
    }

    double time = 0.0;
    if (mode == 0) {
        int dim = stoi(argv[2]);

        char *dataset_path = argv[3];
        char *graph_path = argv[4];
        char *output_path = argv[5];

        vector<Point> points;
        IOUtil::read_input_points(dataset_path, dim, points);
        HeurCoreset heurMD(points);

        if (dim > 2) {
            heurMD.read_IPDG(graph_path);
            heurMD.construct_graph(time);
        } else {
            heurMD.construct_graph_2d(time);
        }

        heurMD.write_G(output_path);
        cout << dataset_path << "," << (time / 1000.0) << endl;

    } else {
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

        HeurCoreset heurMD(points);
        heurMD.read_G(graph_path);

        ofstream output_file;
        output_file.open(output_path, ofstream::out | ofstream::app);

        output_file << "dataset=" << dataset_path << " eps=" << eps;
        output_file.flush();

        cout << "eps=" << eps << endl;

        double query_time = 0.0;
        int size = -1;

        double factors[5] = {4.0, 2.5, 2.0, 1.5, 1.0};

        int round = 0;
        while (round < 5) {
            double delta = factors[round] * eps;
            cout << "delta=" << delta << endl;
            vector<int> result_idx = heurMD.compute_result(delta, time);
            query_time += time;

            vector<Point> coreset;
            coreset.reserve(result_idx.size());
            for (int idx : result_idx)
                coreset.push_back(heurMD.extremes[idx]);
            bool is_valid = Validation::validate(eps, coreset, queries, results);

            if (is_valid) {
                size = coreset.size();
                break;
            }
            round++;
        }

        output_file << " time=" << (query_time / 1000.0) << " size=" << size << "\n";
        output_file.flush();
        output_file.close();
    }

    return 0;
}