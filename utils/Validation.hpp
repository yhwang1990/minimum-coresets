#include <algorithm>
#include <limits>
#include <vector>

#include "Point.hpp"
#include "Point2D.hpp"

using namespace std;

class Validation {
public:
    Validation() = default;

    static bool validate(const double eps, const vector<Point> &points, const vector<Point> &queries,
                         const vector<double> &results) {
        assert(queries.size() <= results.size());
        int n = queries.size();

        if (points.empty())
            return false;

        for (int i = 0; i < n; i++) {
            assert(results[i] > 0);
            double dot_max = 0;
            for (const Point &p : points) {
                double dotp = p.dotP(queries[i]);
                if (dotp > dot_max)
                    dot_max = dotp;
            }

            if (dot_max < (1 - eps) * results[i])
                return false;
        }
        return true;
    }

    static bool validate_eps_kernel(const double eps, const vector<Point> &points, const vector<Point> &queries,
                                    const vector<double> &results) {
        assert(queries.size() <= results.size());
        int n = (int) queries.size() / 2;

        if (points.empty())
            return false;

        for (int i = 0; i < n; i++) {
            assert(results[i * 2] > 0 && results[i * 2 + 1] > 0);
            double dot_max = numeric_limits<double>::min(), dot_min = numeric_limits<double>::min();
            for (const Point &p : points) {
                double dot_p1 = p.dotP(queries[2 * i]);
                double dot_p2 = p.dotP(queries[2 * i + 1]);
                if (dot_p1 > dot_max)
                    dot_max = dot_p1;
                if (dot_p2 > dot_min)
                    dot_min = dot_p2;
            }

            if ((dot_max + dot_min) < (1 - eps) * (results[2 * i] + results[2 * i + 1]))
                return false;
        }
        return true;
    }

    static double calc_loss(const vector<Point> &points, const vector<Point> &queries, const vector<double> &results) {
        assert(queries.size() <= results.size());
        int n = queries.size();

        if (points.empty())
            return 1.0;

        double loss = 0.0;
        for (int i = 0; i < n; i++) {
            assert(results[i] > 0);
            double dot_max = 0;
            for (const Point &p : points) {
                double dotp = p.dotP(queries[i]);
                if (dotp > dot_max)
                    dot_max = dotp;
            }

            if (dot_max <= 0)
                return 1.0;
            else {
                double loss_i = (results[i] - dot_max) / results[i];
                loss = max(loss, loss_i);
            }
        }
        return loss;
    }

    static double
    calc_loss(const vector<Point2D> &points, const vector<Point2D> &queries, const vector<double> &results) {
        assert(queries.size() <= results.size());
        int n = queries.size();

        if (points.empty())
            return 1.0;

        double loss = 0.0;
        for (int i = 0; i < n; i++) {
            assert(results[i] > 0);
            double dot_max = 0;
            for (const Point2D &p : points) {
                double dotp = p.dotP(queries[i]);
                if (dotp > dot_max)
                    dot_max = dotp;
            }

            if (dot_max <= 0)
                return 1.0;
            else {
                double loss_i = (results[i] - dot_max) / results[i];
                loss = max(loss, loss_i);
            }
        }
        return loss;
    }

    static void loss_distribution(const vector<Point> &points, const vector<Point> &queries,
                                  const vector<double> &results, vector<double> &regret_dist) {
        assert(queries.size() <= results.size());
        int n = queries.size();
        regret_dist.reserve(100);

        vector<double> regret_ratios(n);
        for (int i = 0; i < n; i++) {
            assert(results[i] > 0);
            double dot_max = 0;
            for (const Point &p : points) {
                double dotp = p.dotP(queries[i]);
                if (dotp > dot_max)
                    dot_max = dotp;
            }

            double regret_ratio_i = (results[i] - dot_max) / results[i];
            regret_ratios[i] = regret_ratio_i;
        }

        sort (regret_ratios.begin(), regret_ratios.end());

        for (int i = 1; i < 100; ++i) {
            regret_dist[i - 1] = regret_ratios[n * i / 100];
        }
        regret_dist[99] = regret_ratios[n - 1];
    }

    static void loss_distribution(const vector<Point2D> &points, const vector<Point2D> &queries,
                                  const vector<double> &results, vector<double> &regret_dist) {
        assert(queries.size() <= results.size());
        int n = queries.size();
        regret_dist.reserve(100);

        vector<double> regret_ratios(n);
        for (int i = 0; i < n; i++) {
            assert(results[i] > 0);
            double dot_max = 0;
            for (const Point2D &p : points) {
                double dotp = p.dotP(queries[i]);
                if (dotp > dot_max)
                    dot_max = dotp;
            }

            double regret_ratio_i = (results[i] - dot_max) / results[i];
            regret_ratios[i] = regret_ratio_i;
        }

        sort (regret_ratios.begin(), regret_ratios.end());

        for (int i = 1; i < 100; ++i) {
            regret_dist[i - 1] = regret_ratios[n * i / 100];
        }
        regret_dist[99] = regret_ratios[n - 1];
    }
};