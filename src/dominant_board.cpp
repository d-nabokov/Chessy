#include "dominant_board.h"

namespace chessy {

dominant_board::dominant_board(int size)
        : board(size, CHESSMAN_TYPES)
{
    cover_field_ = new int*[size];
    for (int i = 0; i < size; ++i) {
        cover_field_[i] = new int[size];
    }
}

dominant_board::~dominant_board() {
    delete[] cover_field_;
}

void dominant_board::reset() {
    board::reset();
    for (int i = 0; i < size_; ++i) {
        std::memset(cover_field_[i], 0, size_ * sizeof(**cover_field_));
    }
    potential_ = 0;
    uncovered_ = size_ * size_;
}

bool dominant_board::check_chessman(int x, int y, figure f, int *figures_count) const {
    return (field_[x][y] == chessman::empty) && (potential_ >= uncovered_);
}

void dominant_board::set_chessman(int x, int y, figure f) {
    field_[x][y] = f;
    potential_ -= max_weight(f);
    mark_figure(x, y, f, &dominant_board::cover);
}

void dominant_board::unset_chessman(int x, int y, figure f) {
    field_[x][y] = chessman::empty;
    potential_ += max_weight(f);
    mark_figure(x, y, f, &dominant_board::uncover);
}

bool dominant_board::solution_params(int *figures_count) const {
    return false;
}

void dominant_board::init(int *figures_count) {
    board::init(figures_count);
    for (int i = 0; i < indexes_size_; ++i) {
        potential_ += figures_count[i] * max_weight(figure::figure_from_index(i));
    }
}

int dominant_board::max_weight(figure f) const {
    int w = 0;
    switch(f.get_chessman()) {
        case chessman::queen:
            w = 4 * size_ - 3 - even_size();
            break;
        case chessman::rook:
            w = 2 * size_ - 1;
            break;
        case chessman::bishop:
            w = 2 * size_ - 1 - even_size();
            break;
        case chessman::knight:
            w = 9;
            break;
        case chessman::king:
            w = 9;
            break;
        case chessman::pawn:
            w = 3;
            break;
        case chessman::empty:
            w = 0;
            break;
    }
    return w;
}

int dominant_board::even_size() const {
    return 1 ^ (1 & size_);
}

void dominant_board::cover(int &cell) {
    if (cell++ == 0) {
        --uncovered_;
    }
}

void dominant_board::uncover(int &cell) {
    if (cell-- == 1) {
        ++uncovered_;
    }
}

void dominant_board::mark_figure(int x, int y, figure f, void (dominant_board::*func)(int &cell)) {
    (this->*func)(cover_field_[x][y]);

    if (f == chessman::queen || f == chessman::rook) {
        for (int i = 0; i < size_; ++i) {
            if (i == x) {
                continue;
            }
            (this->*func)(cover_field_[i][y]);
        }
        for (int j = 0; j < size_; ++j) {
            if (j == y) {
                continue;
            }
            (this->*func)(cover_field_[x][j]);
        }
    }

    if (f == chessman::queen || f == chessman::bishop) {
        int top_i, top_j;
        // ascending diagonal
        if (x + y < size_) {
            top_i = 0;
            top_j = x + y;
        } else {
            top_i = x + y + 1 - size_;
            top_j = size_ - 1;
        }
        for (int i = top_i, j = top_j; i < size_ && j >= 0; ++i, --j) {
            if (i == x && j == y) {
                continue;
            }
            (this->*func)(cover_field_[i][j]);
        }
        // descending diagonal
        if (y >= x) {
            top_i = 0;
            top_j = y - x;
        } else {
            top_i = x - y;
            top_j = 0;
        }
        for (int i = top_i, j = top_j; i < size_ && j < size_; ++i, ++j) {
            if (i == x && j == y) {
                continue;
            }
            (this->*func)(cover_field_[i][j]);
        }
    }

    if (f == chessman::king) {
        for (int i = std::max(x - 1, 0); i <= std::min(x + 1, size_ - 1); ++i) {
            for (int j = std::max(y - 1, 0); j <= std::min(y + 1, size_ - 1); ++j) {
                if (i == x && j == y) {
                    continue;
                }
                (this->*func)(cover_field_[i][j]);
            }
        }
    }

    if (f == chessman::knight) {
        for (int i = -2; i <= 2; ++i) {
            if (i == 0 || x + i < 0) {
                continue;
            } else if (x + i > size_ - 1) {
                break;
            }

            int j = abs(i) == 2 ? 1 : 2;
            if (y + j < size_) {
                (this->*func)(cover_field_[x + i][y + j]);
            }
            if (y >= j) {
                (this->*func)(cover_field_[x + i][y - j]);
            }
        }
    }

    if (f == chessman::pawn) {
        if (x + 1 < size_) {
            if (y > 0) {
                (this->*func)(cover_field_[x + 1][y - 1]);
            }
            if (y + 1 < size_) {
                (this->*func)(cover_field_[x + 1][y + 1]);
            }
        }
    }
}

board::i_solution dominant_board::get_solution() {
    board::i_solution empty(0);
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            if (cover_field_[i][j] == 0) {
                return empty;
            }
        }
    }
    return board::get_solution();
}

}