#include "IOUtil.h"
#include "RMSUtils.h"

#include <assert.h>
#include <sstream>

void IOUtil::write_output_points(const char *fname, size_t dim, vector<Point> &dataP) {
    FILE *fpt = fopen(fname, "w");

    if (!fpt) {
        cerr << "Cannot open file " << fname << " for writing \n";
        exit(1);
    }

    if (dataP.empty())
        goto done;

    fprintf(fpt, "%ld\n", dim);

    for (size_t i = 0; i < dataP.size(); i++) {
        assert(dim == dataP[i].get_dimension());
        for (size_t j = 0; j < dim; j++) {
            fprintf(fpt, "%lf", dataP[i].get_coordinate(j));
            if (j < dim - 1)
                fprintf(fpt, " ");
        }
        if (i < dataP.size() - 1)
            fprintf(fpt, "\n");
    }

    done:
    fclose(fpt);
}

void IOUtil::read_input_points(const char *fname, size_t dim, vector<Point> &dataP) {

    FILE *fpt = fopen(fname, "r");

    if (!fpt) {
        cerr << "cannot open file " << fname << " for reading \n";
        exit(1);
    }

    double coord;

    while (fscanf(fpt, "%lf", &coord) != EOF) {
        vector<double> coords;
        coords.push_back(coord);
        for (size_t i = 1; i < dim; i++) {
            fscanf(fpt, "%lf", &coord);
            coords.push_back(coord);
        }

        Point p(dim, coords);
        dataP.push_back(p);
    }

    fclose(fpt);
}

void IOUtil::read_validate_dirs(const char *fname, size_t dim, vector<Point> &dataP) {
    FILE *fpt = fopen(fname, "r");

    if (!fpt) {
        cerr << "cannot open file " << fname << " for reading \n";
        exit(1);
    }

    double coord;

    while (fscanf(fpt, "%lf", &coord) != EOF) {
        vector<double> coords;
        coords.push_back(coord);
        for (size_t j = 1; j < dim; j++) {
            fscanf(fpt, "%lf", &coord);
            coords.push_back(coord);
        }
        Point p(dim, coords);
        dataP.push_back(p);
    }
    fclose(fpt);
}

void IOUtil::read_validate_results(const char *fname, vector<double> &results) {
    FILE *fpt = fopen(fname, "r");

    if (!fpt) {
        cerr << "cannot open file " << fname << " for reading \n";
        exit(1);
    }

    double value;
    while (fscanf(fpt, "%lf", &value) != EOF) {
        results.push_back(value);
    }

    fclose(fpt);
}
