#ifndef CHESSY_BOARD_CHECKER_H
#define CHESSY_BOARD_CHECKER_H

#include <cstring>
#include "chessman.h"
#include "solution.h"

namespace chessy {

class board {
protected:
    figure **field_;
    const int size_;
    int *indexes_;
    int indexes_size_;
public:
    using i_solution = solution<int>;

    board(int size, int indexes_size)
        : size_(size), indexes_size_(indexes_size)
    {
        field_ = new figure*[size];
        for (int i = 0; i < size; ++i) {
            field_[i] = new figure[size];
        }
        indexes_ = new int[indexes_size];
        board::reset();
    }

    virtual ~board() {
        for (int i = 0; i < size_; ++i) {
            delete[] field_[i];
        }
        delete[] field_;
        delete[] indexes_;
    }

    int figure_count() const {
        return indexes_[indexes_size_ - 1];
    }

    virtual void init(int *figures_count) {
        std::memset(indexes_, 0, indexes_size_ * sizeof(*indexes_));
        int sum = 0;
        for (int i = 0; i < indexes_size_; ++i) {
            sum += figures_count[i];
            indexes_[i] = sum;
        }
    }

    int get_next_index(int prev_index, int f_number) const {
        int index = prev_index;
        while (indexes_[index] <= f_number) {
            ++index;
        }
        return index;
    }

    virtual void reset() {
        for (int i = 0; i < size_; ++i) {
            std::memset(field_[i], 0, size_ * sizeof(**field_));
        }
    }

    virtual bool check_chessman(int x, int y, figure f, int *figures_count) const = 0;

    virtual void set_chessman(int x, int y, figure f) = 0;
    virtual void unset_chessman(int x, int y, figure f) = 0;

    virtual bool solution_params(int *figures_count) const = 0;

    virtual i_solution get_solution() {
        i_solution s(size_);
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                if (field_[i][j] != chessman::empty) {
                    s.add_figure(i, j, field_[i][j]);
                }
            }
        }
        return s;
    }

    int get_size() const {
        return size_;
    }

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
