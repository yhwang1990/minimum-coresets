#ifndef POINT_HPP
#define POINT_HPP

#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

class Point {
    int dim{};
    vector<double> coords;

public:
    Point() = default;

    explicit Point(int dimension) {
        this->dim = dimension;

        for (int i = 0; i < dimension; i++)
            this->coords.push_back(0);
    }

    Point(int dimension, vector<double> &coordinates) {
        assert(dimension == coordinates.size());

        this->dim = dimension;
        this->coords = coordinates;
    }

    Point operator-(const Point &other_point) const {
        assert(other_point.dim == dim);

        Point diff(dim);

        for (int i = 0; i < dim; i++)
            diff.coords[i] = coords[i] - other_point.coords[i];

        return diff;
    }

    Point operator*(double factor) const {
        Point multiple(dim);

        for (int i = 0; i < dim; i++)
            multiple.coords[i] = coords[i] * factor;

        return multiple;
    }

    void set(int vdim, vector<double> &vcoords) {
        assert(vdim == vcoords.size());

        this->dim = vdim;
        this->coords = vcoords;
    }

    int get_dimension() const { return dim; }

    double get_coordinate(int idx) const {
        assert(idx < dim);

        return coords[idx];
    }

    double distance_to(const Point &other_point) const {
        Point diff = (*this) - other_point;

        return diff.length();
    }

    double length() const {
        double length = 0;

        for (int i = 0; i < dim; i++)
            length += coords[i] * coords[i];

        return sqrt(length);
    }

    double dotP(const Point &other_point) const {
        assert(dim == other_point.dim);

        double dotP = 0.0;
        for (int i = 0; i < dim; i++)
            dotP += coords[i] * other_point.coords[i];

        return dotP;
    }

    void scale_to_length(double len) {
        assert(len >= 0);

        double old_len = length();

        assert(len == 0 || old_len > 0);

        double factor = (old_len > 0) ? (len / old_len) : 0;

        for (int i = 0; i < dim; i++)
            coords[i] *= factor;
    }

    static Point abs(const Point &other_point) {
        Point p(other_point.dim);
        for (int i = 0; i < other_point.dim; i++)
            p.coords[i] = std::abs(other_point.coords[i]);

        return p;
    }

    bool operator<(const Point &other) const {
        assert(this->dim == 2 && other.dim == 2);
        if (this->get_coordinate(1) >= 0 && other.get_coordinate(1) < 0) {
            return true;
        } else if (this->get_coordinate(1) < 0 && other.get_coordinate(1) >= 0) {
            return false;
        } else {
            double atan2_p1 = atan2(this->get_coordinate(1), this->get_coordinate(0));
            double atan2_p2 = atan2(other.get_coordinate(1), other.get_coordinate(0));
            return (atan2_p1 < atan2_p2);
        }
    }
};

#endif //POINT_HPP
