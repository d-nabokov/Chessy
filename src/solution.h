#ifndef CHESSY_SOLUTION_H
#define CHESSY_SOLUTION_H

#include <utility>
#include <unordered_map>
#include <vector>
#include "chessman.h"

namespace chessy {

template<class C>
class solution {
public:
    solution(int size)
        : size_(size)
    {
    }

    solution(solution &&other) = default;

    struct pair_hash;
    using coordinate_t = std::pair<C, C>;
    using map_t = std::unordered_map<coordinate_t, figure, pair_hash>;

    struct pair_hash {
        size_t operator()(const coordinate_t &p) const {
            std::hash<C> h;
            return (h(p.first) << 1) ^ h(p.second);
        }
    };

    void add_figure(const C &x, const C &y, figure f);

    const map_t &get_figures() const;

    bool equal(const solution &other, bool check_colors) const;

    static std::vector<solution> remove_duplicates(std::vector<solution> *l, bool check_colors);

    int get_size() const;

    bool empty() const;

private:
    map_t m_;
    int size_;

    bool find_figure(const C &x, const C &y, figure f, const solution &other) const;
    bool find_opposite_figure(const C &x, const C &y, figure f, const solution &other) const;
};

}


#endif //CHESSY_SOLUTION_H
