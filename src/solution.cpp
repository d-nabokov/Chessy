#include <iostream>
#include "solution.h"

namespace chessy {

template <class C>
void solution<C>::add_figure(const C &x, const C &y, figure f) {
    m_[std::make_pair(x, y)] = f;
}

template <class C>
bool solution<C>::equal(const solution &other, bool check_colors) const {
    if (size_ != other.size_) {
        return false;
    }

    static const int tr_count = 7;
    static bool transformations[2 * tr_count + 1];
    int size = check_colors ? 2 * tr_count + 1 : tr_count;
    for (int i = 0; i < size; ++i) {
        transformations[i] = true;
    }

    for (const auto &p : m_) {
        coordinate_t c = p.first;
        int tr_coords[2 * tr_count] = {
//                // no transformation
//                c.first, c.second,
                // 90 rotation
                size_ - 1 - c.second, c.first,
                // 180 rotation
                size_ - 1 - c.first, size_ - 1 - c.second,
                // 270 rotation
                c.second, size_ - 1 - c.first,
                // horizontal reflection
                size_ - 1 - c.first, c.second,
                // vertical reflection
                c.first, size_ - 1 - c.second,
                // asc diagonal reflection
                size_ - 1 - c.second, size_ - 1 - c.first,
                // desc diagonal reflection
                c.second, c.first
        };

        for (int i = 0; i < tr_count; ++i) {
            if (transformations[i] && !find_figure(tr_coords[2 * i], tr_coords[2 * i + 1], p.second, other)) {
                transformations[i] = false;
            }
            if (check_colors && transformations[i + tr_count] && !find_opposite_figure(tr_coords[2 * i], tr_coords[2 * i + 1], p.second, other)) {
                transformations[i + tr_count] = false;
            }
        }
        if (check_colors && transformations[size - 1] && !find_opposite_figure(c.first, c.second, p.second, other)) {
            transformations[size - 1] = false;
        }
    }
    for (int i = 0; i < size; ++i) {
        if (transformations[i]) {
            return true;
        }
    }

    return false;
}

template <class C>
std::vector<solution<C>> solution<C>::remove_duplicates(std::vector<solution<C>> *l, bool check_colors) {
    std::vector<bool> dupl(l->size(), false);

    for (int i = 0; i + 1 < l->size(); ++i) {
        if (dupl[i]) {
            continue;
        }
        for (int j = i + 1; j < l->size(); ++j) {
            if ((*l)[i].equal((*l)[j], check_colors)) {
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

template <class C>
bool solution<C>::find_figure(const C &x, const C &y, figure f, const solution<C> &other) const {
    auto it = other.m_.find(std::make_pair(x, y));
    return (it != other.m_.end()) && (it->second == f);
}

template <class C>
bool solution<C>::find_opposite_figure(const C &x, const C &y, figure f, const solution<C> &other) const {
    auto it = other.m_.find(std::make_pair(x, y));
    return (it != other.m_.end()) && (it->second.opposite_colors(f));
}


template <class C>
const typename solution<C>::map_t &solution<C>::get_figures() const {
    return m_;
}

template <class C>
int solution<C>::get_size() const {
    return size_;
}

template <class C>
bool solution<C>::empty() const {
    return m_.empty();
}

template class solution<int>;

}