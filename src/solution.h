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
    using map_t = std::unordered_map<coordinate_t, chessman, pair_hash>;

    struct pair_hash {
        size_t operator()(const coordinate_t &p) const {
            std::hash<C> h;
            return (h(p.first) << 1) ^ h(p.second);
        }
    };

    void add_figure(const C &x, const C &y, chessman f);

    std::vector<std::pair<coordinate_t, chessman>> get_figures() const;

    // TODO возвращать список координат с фигурой
//    friend std::ostream &operator<<(std::ostream &os, const solution &s) {
//        os << "******SOLUTION******\n";
//        for (const auto &p : s.m) {
//            coordinate_t coord = p.first;
//            os << coord.first << " " << coord.second << " " << chessman_out(p.second) << "\n";
//        }
//        return os;
//    }

    bool operator==(const solution &other) const;

    static std::vector<solution> remove_duplicates(std::vector<solution> *l);
    static solution get_solution(const chessman **field, int size);

private:
    map_t m;
    int size_;

    bool find_chessman(const C &x, const C &y, chessman f, const solution &other) const;
};

}


#endif //CHESSY_SOLUTION_H
