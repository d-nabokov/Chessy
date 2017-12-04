#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "board.h"

namespace chessy {

board::board(int size)
        : horizontal(new bool[size]), vertical(new bool[size]),
          asc_diagonal(new bool[2 * size - 1]), desc_diagonal(new bool[2 * size - 1]),
          size_(size)
{
    field = new chessman*[size];
    for (int i = 0; i < size; ++i) {
        field[i] = new chessman[size];
    }
    reset();
}

board::~board() {
    for (int i = 0; i < size_; ++i) {
        delete[] field[i];
    }
    delete[] field;
    delete[] horizontal;
    delete[] vertical;
    delete[] asc_diagonal;
    delete[] desc_diagonal;
}

void board::reset() {
    for (int i = 0; i < size_; ++i) {
        std::memset(field[i], static_cast<int>(chessman::empty), size_ * sizeof(**field));
    }
    std::memset(horizontal, 0, size_ * sizeof(*horizontal));
    std::memset(vertical, 0, size_ * sizeof(*vertical));
    std::memset(asc_diagonal, 0, (2 * size_ - 1) * sizeof(*asc_diagonal));
    std::memset(desc_diagonal, 0, (2 * size_ - 1) * sizeof(*desc_diagonal));
}

bool board::check_chessman(int x, int y, chessman f, int *figures) const {
    if (field[x][y] != chessman::empty
        || horizontal[x]
        || vertical[y]
        || asc_diagonal[asc_index(x, y)]
        || desc_diagonal[desc_index(x, y)]) {
        return false;
    }

    if (f == chessman::queen || f == chessman::rook) {
        for (int i = 0; i < size_; ++i) {
            if (field[i][y] != chessman::empty) {
                return false;
            }
        }
        for (int j = 0; j < size_; ++j) {
            if (field[x][j] != chessman::empty) {
                return false;
            }
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
            if (field[i][j] != chessman::empty) {
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
            if (field[i][j] != chessman::empty) {
                return false;
            }
        }
    }

    if (figures[chessman_index(chessman::king)] > 0) {
        for (int i = std::max(x - 1, 0); i <= std::min(x + 1, size_ - 1); ++i) {
            for (int j = std::max(y - 1, 0); j <= std::min(y + 1, size_ - 1); ++j) {
                if (field[i][j] != chessman::empty && (field[i][j] == chessman::king || f == chessman::king)) {
                    return false;
                }
            }
        }
    }

    if (figures[chessman_index(chessman::knight)] > 0) {
        for (int i = -2; i <= 2; ++i) {
            if (i == 0 || x + i < 0) {
                continue;
            } else if (x + i > size_ - 1) {
                break;
            }

            int j = abs(i) == 2 ? 1 : 2;
            if (y + j < size_ && field[x + i][y + j] != chessman::empty &&
                (field[x + i][y + j] == chessman::knight || f == chessman::knight)) {
                return false;
            }
            if (y >= j && field[x + i][y - j] != chessman::empty &&
                (field[x + i][y - j] == chessman::knight || f == chessman::knight)) {
                return false;
            }
        }
    }

    if (figures[chessman_index(chessman::pawn)] > 0) {
        if (f == chessman::pawn && x < size_ - 1) {
            if (y > 0 && field[x + 1][y - 1] != chessman::empty) {
                return false;
            }
            if (y + 1 < size_ && field[x + 1][y + 1] != chessman::empty) {
                return false;
            }
        }
        if (x > 0) {
            if (y > 0 && field[x - 1][y - 1] == chessman::pawn) {
                return false;
            }
            if (y + 1 < size_ && field[x - 1][y + 1] == chessman::pawn) {
                return false;
            }
        }
    }

    return true;
}

void board::set_chessman(int x, int y, chessman f) {
    field[x][y] = f;
    if (f == chessman::queen || f == chessman::rook) {
        horizontal[x] = true;
        vertical[y] = true;
    }

    if (f == chessman::queen || f == chessman::bishop) {
        asc_diagonal[asc_index(x, y)] = true;
        desc_diagonal[desc_index(x, y)] = true;
    }
}

void board::unset_chessman(int x, int y, chessman f) {
    field[x][y] = chessman::empty;
    if (f == chessman::queen || f == chessman::rook) {
        horizontal[x] = false;
        vertical[y] = false;
    }

    if (f == chessman::queen || f == chessman::bishop) {
        asc_diagonal[asc_index(x, y)] = false;
        desc_diagonal[desc_index(x, y)] = false;
    }
}

const chessman **board::get_field() const {
    return const_cast<const chessman **>(field);
}

constexpr int board::asc_index(int x, int y) const {
    return x + y;
}

constexpr int board::desc_index(int x, int y) const {
    return size_ - 1 + x - y;
}

}