#include <cstring>
#include "colorless_independent_board.h"

namespace chessy {

colorless_independent_board::colorless_independent_board(int size)
        : board(size, CHESSMAN_TYPES)
{
    horizontal = new bool[6 * size - 2];
    vertical = horizontal + size;
    asc_diagonal = vertical + size;
    desc_diagonal = asc_diagonal + (2 * size - 1);
}

colorless_independent_board::~colorless_independent_board() {
    delete[] horizontal;
}

void colorless_independent_board::reset() {
    board::reset();
    std::memset(horizontal, 0, (6 * size_ - 2) * sizeof(*horizontal));
}

bool colorless_independent_board::check_chessman(int x, int y, figure f, int *figures_count) const {
    if (field_[x][y] != chessman::empty
        || horizontal[x]
        || vertical[y]
        || asc_diagonal[asc_index(x, y)]
        || desc_diagonal[desc_index(x, y)]) {
        return false;
    }

    if ((has_figure(figures_count, chessman::queen) || has_figure(figures_count, chessman::rook))
            && (f == chessman::queen || f == chessman::rook)) {
        for (int i = 0; i < size_; ++i) {
            if (field_[i][y] != chessman::empty) {
                return false;
            }
        }
        for (int j = 0; j < size_; ++j) {
            if (field_[x][j] != chessman::empty) {
                return false;
            }
        }
    }

    if ((has_figure(figures_count, chessman::queen) || has_figure(figures_count, chessman::bishop))
        && (f == chessman::queen || f == chessman::bishop)) {
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
            if (field_[i][j] != chessman::empty) {
                return false;
            }
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
            if (field_[i][j] != chessman::empty) {
                return false;
            }
        }
    }

    if (has_figure(figures_count, chessman::king)) {
        for (int i = std::max(x - 1, 0); i <= std::min(x + 1, size_ - 1); ++i) {
            for (int j = std::max(y - 1, 0); j <= std::min(y + 1, size_ - 1); ++j) {
                if (field_[i][j] != chessman::empty && (field_[i][j] == chessman::king || f == chessman::king)) {
                    return false;
                }
            }
        }
    }

    if (has_figure(figures_count, chessman::knight)) {
        for (int i = -2; i <= 2; ++i) {
            if (i == 0 || x + i < 0) {
                continue;
            } else if (x + i > size_ - 1) {
                break;
            }

            int j = abs(i) == 2 ? 1 : 2;
            if (y + j < size_ && field_[x + i][y + j] != chessman::empty &&
                (field_[x + i][y + j] == chessman::knight || f == chessman::knight)) {
                return false;
            }
            if (y >= j && field_[x + i][y - j] != chessman::empty &&
                (field_[x + i][y - j] == chessman::knight || f == chessman::knight)) {
                return false;
            }
        }
    }

    if (has_figure(figures_count, chessman::pawn)) {
        if (f == chessman::pawn && x < size_ - 1) {
            if (y > 0 && field_[x + 1][y - 1] != chessman::empty) {
                return false;
            }
            if (y + 1 < size_ && field_[x + 1][y + 1] != chessman::empty) {
                return false;
            }
        }
        if (x > 0) {
            if (y > 0 && field_[x - 1][y - 1] == chessman::pawn) {
                return false;
            }
            if (y + 1 < size_ && field_[x - 1][y + 1] == chessman::pawn) {
                return false;
            }
        }
    }

    return true;
}

void colorless_independent_board::set_chessman(int x, int y, figure f) {
    field_[x][y] = f;
    if (f == chessman::queen || f == chessman::rook) {
        horizontal[x] = true;
        vertical[y] = true;
    }

    if (f == chessman::queen || f == chessman::bishop) {
        asc_diagonal[asc_index(x, y)] = true;
        desc_diagonal[desc_index(x, y)] = true;
    }
}

void colorless_independent_board::unset_chessman(int x, int y, figure f) {
    field_[x][y] = chessman::empty;
    if (f == chessman::queen || f == chessman::rook) {
        horizontal[x] = false;
        vertical[y] = false;
    }

    if (f == chessman::queen || f == chessman::bishop) {
        asc_diagonal[asc_index(x, y)] = false;
        desc_diagonal[desc_index(x, y)] = false;
    }
}

bool colorless_independent_board::solution_params(int *figures_count) const {
    return false;
}

bool colorless_independent_board::has_figure(int *figures_count, chessman c) const {
    return figures_count[chessman_index(c)] > 0;
}

}