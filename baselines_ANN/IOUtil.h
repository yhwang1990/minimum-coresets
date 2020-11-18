#ifndef __IOUTIL_H__
#define __IOUTIL_H__

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include "Point.h"

using namespace std;

class IOUtil {

public:
    IOUtil() = default;

    static void read_input_points(const char *fname, size_t dim, vector<Point> &dataP);
    static void read_validate_dirs(const char *fname, size_t dim, vector<Point> &dataP);
    static void read_validate_results(const char *fname, vector<double> &results);
    static void write_output_points(const char *fname, size_t dim, vector<Point> &dataP);
};

#endif
