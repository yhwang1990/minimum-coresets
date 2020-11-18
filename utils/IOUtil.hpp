#ifndef IOUTIL_HPP
#define IOUTIL_HPP

#include <cassert>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

#include "Point.hpp"
#include "Point2D.hpp"

using namespace std;

class IOUtil {

public:
    IOUtil() = default;

    static void read_input_points(const char *filename, vector<Point2D> &dataP) {
        ifstream input_file(filename);

        if (!input_file.is_open()) {
            cerr << "cannot open file " << filename << " for reading \n";
            exit(1);
        }

        string str;
        while (getline(input_file, str)) {
            double x = 0, y = 0;
            stringstream ss(str);
            ss >> x;
            ss >> y;
            Point2D p(x, y);
            dataP.push_back(p);
        }

        input_file.close();
    }

    static void read_input_points(const char *filename, int dim, vector<Point> &dataP) {
        ifstream input_file(filename);

        if (!input_file.is_open()) {
            cerr << "cannot open file " << filename << " for reading \n";
            exit(1);
        }

        string str;
        double coord = 0;
        while (getline(input_file, str)) {
            vector<double> coords;
            stringstream ss(str);
            for (int i = 0; i < dim; i++) {
                ss >> coord;
                coords.push_back(coord);
            }

            Point p(dim, coords);
            dataP.push_back(p);
        }

        input_file.close();
    }

    static void read_validate_results(const char *filename, vector<double> &results) {
        ifstream input_file(filename);

        if (!input_file.is_open()) {
            cerr << "cannot open file " << filename << " for reading \n";
            exit(1);
        }

        double coord = -1;
        while (!input_file.eof()) {
            input_file >> coord;
            results.push_back(coord);
        }

        input_file.close();
    }

    static void read_topk_results(const char *filename, set<pair<int, int>> &topk_results) {
        ifstream input_file(filename);

        if (!input_file.is_open()) {
            cerr << "cannot open file " << filename << " for reading \n";
            exit(1);
        }

        int q1 = -1, q2 = -1, p1 = -1, p2 = -1;
        double score = -1;
        string str;
        while (getline(input_file, str)) {
            stringstream ss(str);
            ss >> q2;
            ss >> p2;
            ss >> score;

            if (q1 == q2) {
                if (p1 != p2 && score > 0)
                    topk_results.insert(make_pair(p1, p2));
            } else {
                q1 = q2;
                p1 = p2;
            }
        }

        input_file.close();
    }
};

#endif //IOUTIL_HPP
