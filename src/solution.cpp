#include "solution.h"

namespace chessy {

template <class C>
void solution<C>::add_figure(const C &x, const C &y, chessman f) {
    m_[std::make_pair(x, y)] = f;
}

template <class C>
bool solution<C>::operator==(const solution &other) const {
    if (size_ != other.size_) {
        return false;
    }

    static const int variations_count = 8;
    bool variations[variations_count];
    for (int i = 0; i < variations_count; ++i) {
        variations[i] = true;
    }
    // TODO массив с преобразованными координатами, и итерироваться по нему ???

    for (const auto &p : m_) {
        coordinate_t c = p.first;
        // no transformation
        if (variations[0] && !find_chessman(c.first, c.second, p.second, other)) {
            variations[0] = false;
        }
        // 90 rotation
        if (variations[1] && !find_chessman(size_ - 1 - c.second, c.first, p.second, other)) {
            variations[1] = false;
        }
        // 180 rotation
        if (variations[2] && !find_chessman(size_ - 1 - c.first, size_ - 1 - c.second, p.second, other)) {
            variations[2] = false;
        }
        // 270 rotation
        if (variations[3] && !find_chessman(c.second, size_ - 1 - c.first, p.second, other)) {
            variations[3] = false;
        }
        // horizontal reflection
        if (variations[4] && !find_chessman(size_ - 1 - c.first, c.second, p.second, other)) {
            variations[4] = false;
        }
        // vertical reflection
        if (variations[5] && !find_chessman(c.first, size_ - 1 - c.second, p.second, other)) {
            variations[5] = false;
        }
        // asc diagonal reflection
        if (variations[6] && !find_chessman(size_ - 1 - c.second, size_ - 1 - c.first, p.second, other)) {
            variations[6] = false;
        }
        // desc diagonal reflection
        if (variations[7] && !find_chessman(c.second, c.first, p.second, other)) {
            variations[7] = false;
        }
    }
    if (variations[0]) {
        throw std::logic_error("WTF HOW ARE THEY EQUAL?!??!?!?!");
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
bool solution<C>::find_chessman(const C &x, const C &y, chessman f, const solution<C> &other) const {
    auto it = other.m_.find(std::make_pair(x, y));
    return !((it == other.m_.end()) || (it->second != f));
}

template <class C>
solution<C> solution<C>::get_solution(const chessman **field, int size) {
    solution s(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (field[i][j] != chessman::empty) {
                s.add_figure(i, j, field[i][j]);
            }
        }
    }
    return s;
}

template <class C>
const typename solution<C>::map_t &solution<C>::get_figures() const {
//    std::vector<std::pair<coordinate_t, chessman>> ret(m_.size());
//    auto m_it = m_.begin();
//    auto v_it = ret.begin();
//
//    for (; m_it != m_.end(); ++m_it, ++v_it) {
//        *v_it = *m_it;
//    }
//    for (const auto &p : m) {
//        ret.push_back(p);
//    }
    return m_;
}

template <class C>
int solution<C>::get_size() const {
    return size_;
}

template class solution<int>;

}