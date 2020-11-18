#ifndef SET_COVER_H
#define SET_COVER_H

#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class SetCover {
public:
    static void get_min_cover_greedy(int n, const vector<unordered_set<int>> &sets, vector<int> &cov);

    static void intersection(const unordered_set<int> &a, const unordered_set<int> &b, vector<int> &c);
};

class Item {
public:
    int idx, score, round;

    Item(int idx, int score, int round) {
        this->idx = idx;
        this->score = score;
        this->round = round;
    }

    bool operator<(const Item &other_item) const {
        if (this->score < other_item.score)
            return true;
        else if (this->score > other_item.score)
            return false;
        else {
            if (this->round < other_item.round)
                return true;
            else if (this->round > other_item.round)
                return false;
            else
                return (this->idx >= other_item.idx);
        }
    }

    bool operator>(const Item &other_item) const {
        if (this->score > other_item.score)
            return true;
        else if (this->score < other_item.score)
            return false;
        else {
            if (this->round > other_item.round)
                return true;
            else if (this->round < other_item.round)
                return false;
            else
                return (this->idx < other_item.idx);
        }
    }
};

void SetCover::get_min_cover_greedy(int n, const vector<unordered_set<int>> &sets, vector<int> &cov) {
    cov.clear();

    unordered_set<int> uncovered;
    for (int i = 0; i < n; i++)
        uncovered.insert(i);

    priority_queue<Item> queue;
    for (int i = 0; i < n; i++)
        queue.emplace(i, sets[i].size(), 0);

    int round = 1;
    vector<int> tmp;
    while (!uncovered.empty()) {
        Item item = queue.top();
        queue.pop();
        if (item.round == round) {
            cov.push_back(item.idx);
            for (int elem : sets[item.idx])
                uncovered.erase(elem);
            ++round;
        } else {
            intersection(uncovered, sets[item.idx], tmp);
            queue.emplace(item.idx, tmp.size(), round);
        }
    }
}

void SetCover::intersection(const unordered_set<int> &a, const unordered_set<int> &b, vector<int> &c) {
    c.clear();
    if (a.size() >= b.size()) {
        for (int key : b) {
            if (a.find(key) != a.end())
                c.push_back(key);
        }
    } else {
        for (int key : a)
            if (b.find(key) != b.end())
                c.push_back(key);
    }
}

#endif //SET_COVER_H
