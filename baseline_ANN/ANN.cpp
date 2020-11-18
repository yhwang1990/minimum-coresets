#include "ANN.h"
#include <cassert>
#include <stdexcept>

ANN::ANN() {
    init();
}

ANN::~ANN() {
    clean();
}

void ANN::init() {
    tree = NULL;
    pa = NULL;
    data_size = 0;
    dim = 0;
    bucket_size = 1;
    split = ANN_KD_SUGGEST;
    shrink = ANN_BD_SUGGEST;
}

void ANN::clean() {
    if (tree)
        delete tree;
    if (pa)
        annDeallocPts(pa);
    init();
}

void ANN::insertPts(const vector<Point> &dataP) {
    clean();

    data_size = dataP.size();

    if (data_size == 0)
        return;

    //otherwise get dimension from that of first point
    dim = dataP[0].get_dimension();

    pa = annAllocPts(data_size, dim);

    for (size_t i = 0; i < data_size; i++) {
        for (size_t d = 0; d < dim; d++) {
            pa[i][d] = dataP[i].get_coordinate(d);
        }
    }

    //code to fix bucket size - if bucket size is too small we run
    //into too deep a tree which leads to a fault

    bucket_size = 1 + ceil((double) data_size / 10.0);
    //cout << "InsertPts: data_size = " << data_size << " bucket_size = " << bucket_size << endl;
    tree = new ANNbd_tree(pa, data_size, dim, bucket_size, split, shrink);
}

void ANN::getANNs(const vector<Point> &queryP, double epsilon, vector<size_t> &idxs) {
    //if this is an unitialized ANN, this is an incorrect usage
    if (tree == NULL)
        throw std::runtime_error("No points in ANN data structure");

    if (queryP.size() == 0)
        return;

    assert(dim == queryP[0].get_dimension());

    //allocate an array to hold the query points and copy over
    ANNpointArray qa = annAllocPts(queryP.size(), dim);

    for (size_t i = 0; i < queryP.size(); i++) {
        for (size_t d = 0; d < dim; d++)
            qa[i][d] = queryP[i].get_coordinate(d);
    }

    //allocate variables for holding indexes and distances
    ANNidx idx;
    ANNdist dist;

    //do the queries
    for (size_t i = 0; i < queryP.size(); i++) {
        //return only 1-nearest neighbor
        tree->annkSearch(qa[i], 1, &idx, &dist, epsilon);

        //now store the index
        idxs.push_back((size_t) idx);
    }

    annDeallocPts(qa);

    return;
}
