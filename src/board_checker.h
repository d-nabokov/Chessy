#ifndef CHESSY_BOARD_CHECKER_H
#define CHESSY_BOARD_CHECKER_H

#include "chessman.h"

namespace chessy {

class board_checker {
    bool *horizontal;
    bool *vertical;
    bool *asc_diagonal;
    bool *desc_diagonal;
    int size_;
public:
    using chessy::chessman;

    board_checker(int size);

    ~board_checker();


    void reset() {
        std::memset(horizontal, 0, size_);
        std::memset(vertical, 0, size_);
        std::memset(asc_diagonal, 0, 2 * size_ - 1);
        std::memset(desc_diagonal, 0, 2 * size_ - 1);
    }

    bool check_chessman(int x, int y, chessman f, chessman **field) {
        if (field[x][y] != chessman::empty
            || horizontal[x]
            || vertical[y]
            || asc_diagonal[asc_index(x, y)]
            || desc_diagonal[desc_index(x, y)]) {
            return false;
        }

        if (f == chessman::queen || f == chessman::rook) {
            for (int i = 0; i < SIZE; ++i) {
                if (field[i][y] != chessman::empty) {
                    return false;
                }
            }
            for (int j = 0; j < SIZE; ++j) {
                if (field[x][j] != chessman::empty) {
                    return false;
                }
            }
        }

        if (f == chessman::queen || f == chessman::bishop) {
            int top_i, top_j;
            // ascending diagonal
            if (x + y < SIZE) {
                top_i = 0;
                top_j = x + y;
            } else {
                top_i = x + y + 1 - SIZE;
                top_j = SIZE - 1;
            }
            for (int i = top_i, j = top_j; i < SIZE && j >= 0; ++i, --j) {
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
            for (int i = top_i, j = top_j; i < SIZE && j < SIZE; ++i, ++j) {
                if (field[i][j] != chessman::empty) {
                    return false;
                }
            }
        }

        if (figures[chessman_index(chessman::king)] > 0) {
            for (int i = std::max(x - 1, 0); i <= std::min(x + 1, SIZE - 1); ++i) {
                for (int j = std::max(y - 1, 0); j <= std::min(y + 1, SIZE - 1); ++j) {
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
                } else if (x + i > SIZE - 1) {
                    break;
                }

                int j = abs(i) == 2 ? 1 : 2;
                if (y + j < SIZE && field[x + i][y + j] != chessman::empty &&
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
            if (f == chessman::pawn && x < SIZE - 1) {
                if (y > 0 && field[x + 1][y - 1] != chessman::empty) {
                    return false;
                }
                if (y + 1 < SIZE && field[x + 1][y + 1] != chessman::empty) {
                    return false;
                }
            }
            if (x > 0) {
                if (y > 0 && field[x - 1][y - 1] == chessman::pawn) {
                    return false;
                }
                if (y + 1 < SIZE && field[x - 1][y + 1] == chessman::pawn) {
                    return false;
                }
            }
        }

        return true;
    }

private:
    constexpr int asc_index(int x, int y) {
        return x + y;
    }

    constexpr int desc_index(int x, int y) {
        return SIZE - 1 + x - y;
    }
};

}


#endif //CHESSY_BOARD_CHECKER_H
