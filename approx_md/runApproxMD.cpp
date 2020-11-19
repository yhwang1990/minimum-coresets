#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <random>
#include <ANN/ANN.h>

#include "Point.hpp"
#include "IOUtil.hpp"
#include "SetCover.hpp"

using namespace std;

vector<Point> queries;
vector<double> results;

default_random_engine generator(0);
normal_distribution<double> distribution(0.0, 1.0);

void get_rand_dir(int dim, ANNpoint p) {
    double len = 0;
    while (len == 0) {
        for (int i = 0; i < dim; i++) {
            p[i] = distribution(generator);
            len += (p[i] * p[i]);
        }
        len = sqrt(len);
    }
    for (int i = 0; i < dim; i++)
        p[i] = p[i] / len;
    p[dim] = 0;
}

double inner_product(int dim, const ANNpoint &p, const ANNpoint &q) {
    double sum = 0;
    for (int i = 0; i < dim; i++) {
        sum += (p[i] * q[i]);
    }
    return sum;
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

    ANNpointArray dataPts;
    ANNpoint queryPt;
    ANNidxArray firstIdx;
    ANNdistArray firstDist;
    ANNkd_tree *kdTree;

    queryPt = annAllocPt(dim + 1);
    dataPts = annAllocPts(points.size(), dim + 1);

    firstIdx = new ANNidx[1];
    firstDist = new ANNdist[1];

    for (int i = 0; i < points.size(); ++i) {
        double sum = 0.0;
        for (int j = 0; j < dim; ++j) {
            dataPts[i][j] = points[i].get_coordinate(j);
            sum += (dataPts[i][j] * dataPts[i][j]);
        }
        dataPts[i][dim] = sqrt(dim - sum);
    }

    kdTree = new ANNkd_tree(dataPts, points.size(), dim + 1);

    vector<int> coresetIdxs;
    int ss = 16;
    int uIdx = 0;

    vector<unordered_set<int>> setSystem;
    setSystem.reserve(points.size());

    bool isValid = false;
    while (!isValid) {
        clock_t clockS = clock();

        for (int i = 0; i < ss; ++i) {
            get_rand_dir(dim, queryPt);
            kdTree->annkSearch(queryPt, 1, firstIdx, firstDist, 0);

            set<int> resultIdxs;
            resultIdxs.insert(firstIdx[0]);

            ANNdist sqRad = dim + 1.0 - 2.0 * (1 - epsilon / 2.0) * inner_product(dim, queryPt, dataPts[firstIdx[0]]);

            auto approxIdx = new ANNidx[points.size()];
            auto approxDist = new ANNdist[points.size()];

            kdTree->annkFRSearch(queryPt, sqRad, points.size(), approxIdx, approxDist);

            for (int idx = 0; idx < points.size(); ++idx) {
                if (approxIdx[idx] != ANN_NULL_IDX) {
                    resultIdxs.insert(approxIdx[idx]);
                } else {
                    break;
                }
            }

            for (int pIdx : resultIdxs) {
                setSystem[pIdx].insert(uIdx);
            }

            ++uIdx;
        }

        coresetIdxs.clear();
        SetCover::get_min_cover_greedy(uIdx, setSystem, coresetIdxs);

        clock_t clockE = clock();
        time += (double) (clockE - clockS);

        isValid = validate(points, coresetIdxs, epsilon);

        cout << uIdx << "," << coresetIdxs.size() << "," << isValid << endl;

        if (ss < 1000000)
            ss = 2 * ss;
    }

    return coresetIdxs;
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

    double time = 0;
    vector<int> coresetIdxs = approx_coreset(points, eps, time);

    int size = coresetIdxs.size();
    time = (double) time / 1000.0;

    output_file << "time=" << time << " size=" << size << "\n" << flush;

    output_file << "\n" << flush;
    output_file.close();
}
