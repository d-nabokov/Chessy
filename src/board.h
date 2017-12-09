#ifndef CHESSY_BOARD_CHECKER_H
#define CHESSY_BOARD_CHECKER_H

#include "chessman.h"
#include "solution.h"

namespace chessy {

class board {
protected:
    chessman **field;
    const int size_;
public:
    using i_solution = solution<int>;

    board(int size)
        : size_(size)
    {
        field = new chessman*[size];
        for (int i = 0; i < size; ++i) {
            field[i] = new chessman[size];
        }
        board::reset();
    }

    virtual ~board() {
        for (int i = 0; i < size_; ++i) {
            delete[] field[i];
        }
        delete[] field;
    }

    virtual void reset() {
        for (int i = 0; i < size_; ++i) {
            std::memset(field[i], static_cast<int>(chessman::empty), size_ * sizeof(**field));
        }
    }

    virtual bool check_chessman(int x, int y, chessman f, int *figures) const = 0;

    virtual void set_chessman(int x, int y, chessman f) = 0;
    virtual void unset_chessman(int x, int y, chessman f) = 0;

    virtual i_solution get_solution() = 0;

protected:
    int asc_index(int x, int y) const {
        return x + y;
    }
    int desc_index(int x, int y) const {
        return size_ - 1 + x - y;
    }
};

}


#endif //CHESSY_BOARD_CHECKER_H
