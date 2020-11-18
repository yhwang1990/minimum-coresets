#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <random>

#include "Point.hpp"
#include "IOUtil.hpp"

using namespace std;

vector<Point> queries;
vector<double> results;

default_random_engine generator(0);
normal_distribution<double> distribution(0.0, 1.0);

Point get_rand_dir(int dim) {
    vector<double> coords(dim);
    double len = 0;
    for (int i = 0; i < dim; i++) {
        coords[i] = distribution(generator);
        len += (coords[i] * coords[i]);
    }
    len = sqrt(len);
    for (int i = 0; i < dim; i++)
        coords[i] = coords[i] / len;
    Point p(dim, coords);
    return p;
}

bool validate(const vector<Point> &points, vector<int> &idx, double epsilon) {
    assert(idx.size() <= points.size());

    if (points.empty())
        return true;

    if (idx.empty())
        return false;

    assert(idx[0] >= 0 && idx[idx.size() - 1] < points.size());

    for (int i = 0; i < queries.size(); i++) {
        double cor_max = points[idx[0]].dotP(queries[i]);
        for (int j = 1; j < idx.size(); j++) {
            double cor_val = points[idx[j]].dotP(queries[i]);
            if (cor_val > cor_max)
                cor_max = cor_val;
        }

        double pt_val = results[i];
        if (cor_max < (1 - epsilon) * pt_val)
            return false;
    }
    return true;
}

vector<int> approx_coreset(const vector<Point> &points, const double epsilon, double &time) {
    int dim = points[0].get_dimension();

    vector<int> idx;
    size_t ss = 16;
    bool cond = false;
    while (!cond) {
        clock_t clockS = clock();

        vector<Point> randomDirs;

        get_rand_dir(1.0, dim, ss, randomP, false);

        vector<set<size_t>> DSets;
        int k = 1;
        int flag;
        for (size_t i = 0; i < ss; i++) {
            set<size_t> DSet;
            vector<size_t> topkI;
            vector<double> topkV;
            size_t k1 = (10 * k <= fatP.size()) ? 10 * k : fatP.size();

            rank_selection_dotp(fatP, randomP[i], k1, topkI, topkV);

            assert(topkV[k1 - 1] >= 0);
            flag = 1;
            for (size_t j = 0; j < idxs.size(); j++) {
                if (fatP[idxs[j]].dotP(randomP[i]) >= (1 - epsilon) * topkV[k - 1]) {
                    flag = 0;
                }
            }
            if (flag == 1) {
                for (size_t j = 0; j < k1; j++) {
                    if (topkV[j] >= (1 - epsilon) * topkV[k - 1]) {
                        DSet.insert(topkI[j]);
                    } else {
                        break;
                    }
                }
                DSets.push_back(DSet);
            }
        }

        vector<size_t> idxs2;
        HSApprox::get_hs_approximation<size_t>(DSets, idxs2);
        for (size_t j = 0; j < idxs2.size(); j++) {
            idxs.push_back(idxs2[j]);
        }

        clock_t clockE = clock();
        time += (double) (clockE - clockS);

        cond = validate(points, idx, epsilon);
        ss = 2 * ss;
    }

    return idx;
}

int main(int argc, char **argv) {
    int dim = stoi(argv[1]);
    double eps = stod(argv[2]);
    char *dataset_path = argv[3];
    char *dirs_path = argv[4];
    char *validation_path = argv[5];
    char *output_path = argv[6];

    vector<Point> points;

    IOUtil::read_input_points(dataset_path, dim, points);
    IOUtil::read_input_points(dirs_path, dim, queries);
    IOUtil::read_validate_results(validation_path, results);

    ofstream output_file;
    output_file.open(output_path, std::ofstream::out | std::ofstream::app);

    cout << "approx " << dataset_path << " " << points.size() << " " << dim << endl;

    output_file << "dataset=" << argv[3] << " eps=" << eps << "\n" << flush;
    output_file.flush();

    vector<size_t> idx;
    double time = 0;
    idx = approx_coreset(points, eps, time);

    int size = idx.size();
    time = (double) time / 1000.0;

    output_file << "time=" << time << " size=" << size << "\n" << flush;

    output_file << "\n" << flush;
    output_file.close();
}
