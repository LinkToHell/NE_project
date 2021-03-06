#include <vector>
#include <serialization.h>

using namespace std;

class connect {
private:
    uint64_t n1, n2;
    vector<v> g1, g2;
    vector<int> c_count;
    vector<vector<int>> c_nums;

    bool next_monotonic(vector<int> &v) {
        ++v.back();
        int i = static_cast<int>(v.size() - 1);
        for (; i != 0 && v[i] == n2; --i, ++v[i]) {}
        for (int j = i + 1; j != v.size(); v[j] = v[i], ++j) {}
        return v.front() != n2;
    }

    bool not_all_dif(vector<int> &v) {
        vector<bool> count(n2);
        for (int i : v) {
            if (count[i]) {
                return true;
            } else {
                count[i] = true;
            }
        }
        return false;
    }

    bool next_con_nums(vector<int> &v) {
        while (next_monotonic(v) && not_all_dif(v)) {}
        return v.front() != n2;
    }

public:
    vector<v> g_cur;

    connect(vector<v> g1_p, vector<v> g2_p, vector<int> c_count_p) : n1(g1_p.size()), n2(g2_p.size()),
                                                                     c_count(move(c_count_p)), g1(move(g1_p)),
                                                                     g2(move(g2_p)),
                                                                     c_nums(g1.size()),
                                                                     g_cur(g1.size() + g2.size()) {
        for (int i = 0; i != n1; ++i) {
            g_cur[i] = g1[i];
            g_cur[i].degree += c_count[i];
            c_nums[i].resize(c_count[i]);
            if (not_all_dif(c_nums[i])) {
                next_con_nums(c_nums[i]);
            }
        }
        for (int i = 0; i != n2; ++i) {
            g_cur[n1 + i] = g2[i];
            for (int &j : g_cur[n1 + i].out) {
                j += n1;
            }
        }
        for (int i = 0; i != n1; ++i) {
            for (int j = 0; j != c_count[i]; ++j) {
                g_cur[i].out.push_back(n1 + c_nums[i][j]);
            }
        }
    }

    bool next() {
        for (int i = 0; i != n1; ++i) {
            for (int j = 0; j != c_count[i]; ++j) {
                g_cur[i].out.pop_back();
            }
        }
        for (int i = 0; i != n1; ++i) {
            if (!next_con_nums(c_nums[i])) {
                c_nums[i].assign(c_count[i], 0);
                if (not_all_dif(c_nums[i])) {
                    next_con_nums(c_nums[i]);
                }
            } else {
                for (int j = 0; j != n1; ++j) {
                    for (int k = 0; k != c_count[j]; ++k) {
                        g_cur[j].out.push_back(n1 + c_nums[j][k]);
                    }
                }
                if (c_nums[n1 - 1][0] != 0) { //only for simetric cycles
                    return false;
                }
                return true;
            }
        }
        return false;
    }
};

int main() {
    vector<v> g1, g2;
    vector<int> c_count;
    read_graph(g1);
    read_graph(g2);
    read_vector(c_count);
    connect g_con(g1, g2, c_count);
    do {
        write_size(g1.size());
        write_graph(g_con.g_cur);
    } while (g_con.next());
    return 0;
}
