#include "solution.h"

namespace chessy {

void solution::add_figure(const C &x, const C &y, chessman f) {
    m[std::make_pair(x, y)] = f;
}

bool solution::operator==(const solution &other) const {
    static const int variations_count = 8;
    bool variations[variations_count];
    // TODO массив с преобразованными координатами, и итерироваться по нему
    for (int i = 0; i < variations_count; ++i) {
        variations[i] = true;
    }

    for (const auto &p : m) {
        coordinate_t c = p.first;
        // no transformation
        if (variations[0] && !find_chessman(c.first, c.second, p.second, other)) {
            variations[0] = false;
        }
        // 90 rotation
        if (variations[1] && !find_chessman(SIZE - 1 - c.second, c.first, p.second, other)) {
            variations[1] = false;
        }
        // 180 rotation
        if (variations[2] && !find_chessman(SIZE - 1 - c.first, SIZE - 1 - c.second, p.second, other)) {
            variations[2] = false;
        }
        // 270 rotation
        if (variations[3] && !find_chessman(c.second, SIZE - 1 - c.first, p.second, other)) {
            variations[3] = false;
        }
        // horizontal reflection
        if (variations[4] && !find_chessman(SIZE - 1 - c.first, c.second, p.second, other)) {
            variations[4] = false;
        }
        // vertical reflection
        if (variations[5] && !find_chessman(c.first, SIZE - 1 - c.second, p.second, other)) {
            variations[5] = false;
        }
        // asc diagonal reflection
        if (variations[6] && !find_chessman(SIZE - 1 - c.second, SIZE - 1 - c.first, p.second, other)) {
            variations[6] = false;
        }
        // desc diagonal reflection
        if (variations[7] && !find_chessman(c.second, c.first, p.second, other)) {
            variations[7] = false;
        }
    }
    for (int i = 0; i < variations_count; ++i) {
        if (variations[i]) {
            return true;
        }
    }
    return false;
}

static std::vector<solution> solution::remove_duplicates(std::vector<solution> *l) {
    std::vector<bool> dupl(l->size(), false);

    for (int i = 0; i + 1 < l->size(); ++i) {
        if (dupl[i]) {
            continue;
        }
        for (int j = i + 1; j < l->size(); ++j) {
            if ((*l)[i] == (*l)[j]) {
                dupl[j] = true;
            }
        }
    }

    std::vector<solution> ret;
    for (int i = 0; i < l->size(); ++i) {
        if (!dupl[i]) {
            ret.push_back(std::move((*l)[i]));
        }
    }

    return ret;

}

bool solution::find_chessman(const C &x, const C &y, chessman f, const solution &other) const {
    auto it = other.m.find(std::make_pair(x, y));
    return !((it == other.m.end()) || (it->second != f));
}

}