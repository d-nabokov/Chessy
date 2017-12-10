#include "solution.h"

namespace chessy {

template <class C>
void solution<C>::add_figure(const C &x, const C &y, figure f) {
    m_[std::make_pair(x, y)] = f;
}

template <class C>
bool solution<C>::operator==(const solution &other) const {
    if (size_ != other.size_) {
        return false;
    }

    static const int variations_count = 7;
    bool variations[variations_count];
    for (int i = 0; i < variations_count; ++i) {
        variations[i] = true;
    }

    for (const auto &p : m_) {
        coordinate_t c = p.first;
        int tr_coords[2 * variations_count] = {
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

        for (int i = 0; i < variations_count; ++i) {
            if (variations[i] && !find_figure(tr_coords[2 * i], tr_coords[2 * i + 1], p.second, other)) {
                variations[i] = false;
            }
        }
    }
    for (int i = 0; i < variations_count; ++i) {
        if (variations[i]) {
            return true;
        }
    }
    return false;
}

template <class C>
std::vector<solution<C>> solution<C>::remove_duplicates(std::vector<solution<C>> *l) {
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

template <class C>
bool solution<C>::find_figure(const C &x, const C &y, figure f, const solution<C> &other) const {
    auto it = other.m_.find(std::make_pair(x, y));
    return !((it == other.m_.end()) || (it->second != f));
}


template <class C>
const typename solution<C>::map_t &solution<C>::get_figures() const {
    return m_;
}

template <class C>
int solution<C>::get_size() const {
    return size_;
}

template class solution<int>;

}