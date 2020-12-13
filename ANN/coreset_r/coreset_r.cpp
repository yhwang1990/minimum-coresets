#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/numeric/ublas/matrix.hpp>

#include "../Point.h"
#include "../ANN.h"
#include "../RMSUtils.h"
#include "../IOUtil.h"

using namespace std;

vector<Point> validDirs;
vector<double> validResults;

bool validate_coreset(const vector<Point> &fatP, vector<size_t> &idxs, double epsilon) {
    assert(idxs.size() <= fatP.size());

    if (fatP.empty())
        return true;

    if (idxs.empty())
        return false;

    assert(idxs[0] >= 0 && idxs[idxs.size() - 1] < fatP.size());

    for (size_t i = 0; i < validDirs.size(); i++) {
        double cor_max = fatP[idxs[0]].dotP(validDirs[i]);
        for (size_t j = 1; j < idxs.size(); j++) {
            double corval = fatP[idxs[j]].dotP(validDirs[i]);
            if (corval > cor_max)
                cor_max = corval;
        }

        double ptval = validResults[i];
        if (cor_max < (1 - epsilon) * ptval)
            return false;
    }
    return true;
}

void loss_distribution(const vector<Point> &coreset, const vector<Point> &queries,
                       const vector<double> &results, vector<double> &regret_dist) {
    int n = min(queries.size(), results.size());
    regret_dist.reserve(1000);

    vector<double> regret_ratios(n);
    for (int i = 0; i < n; i++) {
        assert(results[i] > 0);
        double dot_max = 0;
        for (int j = 0; j < coreset.size(); ++j) {
            double dotp = coreset[j].dotP(queries[i]);
            if (dotp > dot_max)
                dot_max = dotp;
        }

        double regret_ratio_i = (results[i] - dot_max) / results[i];
        regret_ratios[i] = regret_ratio_i;
    }

    sort (regret_ratios.begin(), regret_ratios.end());

    for (int i = 1; i < 1000; ++i) {
        regret_dist[i - 1] = regret_ratios[n * i / 1000];
    }
    regret_dist[999] = regret_ratios[n - 1];
}

bool validate_eps_kernel(const vector<Point> &fatP, vector<size_t> &idxs, double epsilon) {
    assert(idxs.size() <= fatP.size());

    if (fatP.empty())
        return true;

    if (idxs.empty())
        return false;

    assert(idxs[0] >= 0 && idxs[idxs.size() - 1] < fatP.size());

    size_t m = validDirs.size() / 2;
    for (size_t i = 0; i < m; i++) {
        double cor_max = fatP[idxs[0]].dotP(validDirs[2 * i]);
        double cor_min = fatP[idxs[0]].dotP(validDirs[2 * i + 1]);
        for (size_t j = 1; j < idxs.size(); j++) {
            double cor_val1 = fatP[idxs[j]].dotP(validDirs[2 * i]);
            double cor_val2 = fatP[idxs[j]].dotP(validDirs[2 * i + 1]);
            if (cor_val1 > cor_max)
                cor_max = cor_val1;
            if (cor_val2 > cor_min)
                cor_min = cor_val2;
        }

        if ((cor_max + cor_min) < (1 - epsilon) * (validResults[2 * i] + validResults[2 * i + 1]))
            return false;
    }
    return true;
}

void coreset_by_sample(ANN *ann_ds, size_t dim, double outer_rad, double delta, size_t deltam, vector<size_t> &idxs) {
    vector<Point> randomP;
    RMSUtils::get_random_sphere_points(outer_rad, dim, deltam, randomP, false);

    vector<size_t> new_idxs;
    ann_ds->getANNs(randomP, delta, new_idxs);

    //figure out all the distinct indices
    set<size_t> unique_idxs;
    for (size_t i = 0; i < idxs.size(); i++)
        unique_idxs.insert(idxs[i]);
    for (size_t i = 0; i < new_idxs.size(); i++)
        unique_idxs.insert(new_idxs[i]);

    idxs.clear();

    set<size_t>::iterator it;
    for (it = unique_idxs.begin(); it != unique_idxs.end(); ++it)
        idxs.push_back((*it));
}

vector<size_t> get_coreset(const vector<Point> &fatP, const int r, const double epsilon, bool &isValid) {
    size_t dim = fatP[0].get_dimension();

    double outer_rad;
    outer_rad = 1 + sqrt(dim);
    double delta = epsilon / (2 * outer_rad);

    vector<size_t> idxs;
    ANN *ann_ds = new ANN();
    ann_ds->insertPts(fatP);

    size_t m = r;
    bool b = false;
    while (!b) {
        coreset_by_sample(ann_ds, dim, outer_rad, delta, m, idxs);
        b = validate_coreset(fatP, idxs, epsilon);
        m += 5;

        if (b && idxs.size() <= r) {
            isValid = true;
            break;
        }

        if (idxs.size() > r) {
            isValid = false;
            break;
        }
    }

    delete ann_ds;
    return idxs;
}

int main(int argc, char **argv) {
    if (argc < 7) {
        cerr << "coreset: Usage " << argv[0] << "<r> <dim> <data_path> <query_path> <valid_path> <output_path>\n";
        exit(1);
    }

    int r = atoi(argv[1]);
    size_t dim = atoi(argv[2]);

    vector<Point> fatP;

    IOUtil::read_input_points(argv[3], dim, fatP);
    IOUtil::read_validate_dirs(argv[4], dim, validDirs);
    IOUtil::read_validate_results(argv[5], validResults);

    ofstream result_file;
    result_file.open(argv[6], ofstream::out | ofstream::app);

    cout << "ann " << argv[3] << " " << fatP.size() << " " << dim << endl;

    result_file << "dataset=" << argv[3] << " r=" << r << "\n" << flush;

    double eps = 0.2;

    vector<size_t> idxs;
    bool isValid;
    while (true) {
        cout << eps << endl;
        idxs = get_coreset(fatP, r, eps, isValid);
        if (isValid) {
            break;
        } else {
            eps += 0.01;
        }
    }

    vector<Point> coreset;
    vector<double> regretDist;
    coreset.reserve(idxs.size());
    for (int i = 0; i < idxs.size(); ++i)
        coreset.push_back(fatP[idxs[i]]);
    loss_distribution(coreset, validDirs, validResults, regretDist);

    cout << regretDist[999] << endl;

    for (int i = 0; i < 1000; ++i)
        result_file << regretDist[i] << "\n";
    result_file.flush();
    result_file.close();
}
