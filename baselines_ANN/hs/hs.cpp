#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>

#include "../HittingSet.h"
#include "../RandUtil.h"
#include "../IOUtil.h"
#include "../RMSUtils.h"

using namespace std;

vector<Point> validDirs;
vector<double> validResults;

bool validate_hs(const vector<Point> &fatP, vector<size_t> &idxs, double epsilon) {
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

void hs_by_sampling(vector<Point> fatP, size_t dim, double epsilon, size_t ss, vector<size_t> &idxs) {
    vector<Point> randomP;
    RMSUtils::get_random_sphere_points(1.0, dim, ss, randomP, false);

    vector<set<size_t> > DSets;
    int k = 1;
    int flag;
    for (size_t i = 0; i < ss; i++) {
        set<size_t> DSet;
        vector<size_t> topkI;
        vector<double> topkV;
        size_t k1 = (10 * k <= fatP.size()) ? 10 * k : fatP.size();

        RMSUtils::rank_selection_dotp(fatP, randomP[i], k1, topkI, topkV);

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
}

vector<size_t> get_hs(const vector<Point> &dataP, const double epsilon, double &time) {
    size_t dim = dataP[0].get_dimension();

    vector<size_t> idxs;
    size_t ss = 10;
    bool cond = false;
    while (!cond) {
        clock_t clockS = clock();
        hs_by_sampling(dataP, dim, epsilon / 5, ss, idxs);
        clock_t clockE = clock();
        time += (double) (clockE - clockS);

        cond = validate_hs(dataP, idxs, epsilon);
        ss = 2 * ss;
    }

    return idxs;
}

int main(int argc, char **argv) {
    if (argc < 7) {
        cerr << "hs: Usage " << argv[0] << "<eps> <dim> <data_path> <query_path> <valid_path> <output_path>\n";
        exit(1);
    }

    double eps = atof(argv[1]);
    size_t dim = atoi(argv[2]);

    vector<Point> dataP;

    IOUtil::read_input_points(argv[3], dim, dataP);
    IOUtil::read_validate_dirs(argv[4] ,dim, validDirs);
    IOUtil::read_validate_results(argv[5], validResults);

    ofstream result_file;
    result_file.open(argv[6], ofstream::out | ofstream::app);

    cout << "hs " << argv[3] << " " << dataP.size() << " " << dim << endl;

    result_file << "dataset=" << argv[3] << " eps=" << eps << "\n" << flush;

    for (int r = 0; r < 10; ++r) {
        vector<size_t> idxs;
        double time = 0;
        idxs = get_hs(dataP, eps, time);

        int size = idxs.size();
        time = (double) time / CLOCKS_PER_SEC;

        result_file << "time=" << (time * 1000.0) << " size=" << size << "\n" << flush;
    }
    result_file << "\n" << flush;
    result_file.close();
}
