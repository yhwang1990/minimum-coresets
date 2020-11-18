#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <cassert>
#include <cmath>

using namespace std;

class Point2D {
public:
    double x, y;

    Point2D() {
        this->x = 0.0;
        this->y = 0.0;
    }

    Point2D(double x1, double y1) {
        this->x = x1;
        this->y = y1;
    }

    Point2D operator-(const Point2D &other_point) const {
        Point2D diff;

        diff.x = this->x - other_point.x;
        diff.y = this->y - other_point.y;

        return diff;
    }

    Point2D operator*(double factor) const {
        Point2D multi;

        multi.x = this->x * factor;
        multi.y = this->y * factor;

        return multi;
    }

    bool operator<(const Point2D &other_point) const {
        if (this->y >= 0 && other_point.y < 0) {
            return true;
        } else if (this->y < 0 && other_point.y >= 0) {
            return false;
        } else {
            double atan2_p1 = atan2(this->y, this->x);
            double atan2_p2 = atan2(other_point.y, other_point.x);
            return (atan2_p1 < atan2_p2);
        }
    }

    void set(double x1, double y1) {
        this->x = x1;
        this->y = y1;
    }

    double distance_to(const Point2D &other_point) const {
        Point2D diff = (*this) - other_point;
        return diff.length();
    }

    double length() const {
        double length = this->x * this->x + this->y * this->y;
        return sqrt(length);
    }

    double dotP(const Point2D &other_point) const {
        double dotP = this->x * other_point.x + this->y * other_point.y;
        return dotP;
    }

    void scale_to_length(double len) {
        assert(len >= 0);

        double old_len = length();

        assert(len == 0 || old_len > 0);

        double factor = (old_len > 0) ? (len / old_len) : 0;

        this->x *= factor;
        this->y *= factor;
    }
};

#endif //POINT2D_HPP
