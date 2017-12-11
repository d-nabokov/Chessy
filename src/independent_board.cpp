#include "independent_board.h"

namespace chessy {

independent_board::independent_board(int size)
        : board(size, 2 * CHESSMAN_TYPES)
{
}

independent_board::~independent_board() {

}

void independent_board::reset() {
    board::reset();
}

bool independent_board::check_chessman(int x, int y, figure f, int *figures_count) const {
    if (field_[x][y] != chessman::empty) {
        return false;
    }
    if (f.get_color() == color::white) {
        return true;
    }

    if (has_figure(figures_count, chessman::queen) || has_figure(figures_count, chessman::rook)) {
        bool is_qr = f == chessman::queen || f == chessman::rook;
        for (int i = x + 1; i < size_; ++i) {
            if (field_[i][y] != chessman::empty) {
                if (is_attack_each_other(is_qr, field_[i][y], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
        for (int i = x - 1; i >= 0; --i) {
            if (field_[i][y] != chessman::empty) {
                if (is_attack_each_other(is_qr, field_[i][y], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
        for (int j = y + 1; j < size_; ++j) {
            if (field_[x][j] != chessman::empty) {
                if (is_attack_each_other(is_qr, field_[x][j], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
        for (int j = y - 1; j >= 0; --j) {
            if (field_[x][j] != chessman::empty) {
                if (is_attack_each_other(is_qr, field_[x][j], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
    }

    if (has_figure(figures_count, chessman::queen) || has_figure(figures_count, chessman::bishop)) {
        bool is_qb = f == chessman::queen || f == chessman::bishop;
        for (int i = 1; x + i < size_ && y + i < size_; ++i) {
            if (field_[x + i][y + i] != chessman::empty) {
                if (is_attack_each_other(is_qb, field_[x + i][y + i], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
        for (int i = 1; x + i < size_ && y >= i; ++i) {
            if (field_[x + i][y - i] != chessman::empty) {
                if (is_attack_each_other(is_qb, field_[x + i][y - i], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
        for (int i = 1; x >= i && y + i < size_; ++i) {
            if (field_[x - i][y + i] != chessman::empty) {
                if (is_attack_each_other(is_qb, field_[x - i][y + i], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
        for (int i = 1; x + i < size_ && y >= i; ++i) {
            if (field_[x - i][y - i] != chessman::empty) {
                if (is_attack_each_other(is_qb, field_[x - i][y - i], chessman::queen, chessman::rook)) {
                    return false;
                }
                break;
            }
        }
    }

    if (has_figure(figures_count, chessman::king)) {
        bool is_k = f == chessman::king;
        for (int i = std::max(x - 1, 0); i <= std::min(x + 1, size_ - 1); ++i) {
            for (int j = std::max(y - 1, 0); j <= std::min(y + 1, size_ - 1); ++j) {
                if (field_[i][j] != chessman::empty && is_attack_each_other(is_k, field_[i][j], chessman::king)) {
                    return false;
                }
            }
        }
    }

    if (has_figure(figures_count, chessman::knight)) {
        bool is_n = f == chessman::knight;
        for (int i = -2; i <= 2; ++i) {
            if (i == 0 || x + i < 0) {
                continue;
            } else if (x + i > size_ - 1) {
                break;
            }

            int j = abs(i) == 2 ? 1 : 2;
            if (y + j < size_ && field_[x + i][y + j] != chessman::empty &&
                    is_attack_each_other(is_n, field_[x + i][y + j], chessman::knight)) {
                return false;
            }
            if (y >= j && field_[x + i][y - j] != chessman::empty &&
                    is_attack_each_other(is_n, field_[x + i][y - j], chessman::knight)) {
                return false;
            }
        }
    }

    if (has_figure(figures_count, chessman::pawn)) {
        if (x > 0) {
            if (y > 0 && field_[x - 1][y - 1] != chessman::empty
                && ((f == chessman::pawn && field_[x - 1][y - 1].get_color() == color::white)
                    || is_white_chessman(field_[x - 1][y - 1], chessman::pawn))) {
                return false;
            }
            if (y + 1 < size_ && field_[x - 1][y + 1] != chessman::empty
                && ((f == chessman::pawn && field_[x - 1][y + 1].get_color() == color::white)
                    || is_white_chessman(field_[x - 1][y + 1], chessman::pawn))) {
                return false;
            }
        }
    }

    return true;
}

void independent_board::set_chessman(int x, int y, figure f) {
    field_[x][y] = f;
}

void independent_board::unset_chessman(int x, int y, figure f) {
    field_[x][y] = chessman::empty;
}

bool independent_board::has_figure(int *figures_count, chessman c) const {
    int index = chessman_index(c);
    return figures_count[index] > 0 || figures_count[index + CHESSMAN_TYPES] > 0;
}

bool independent_board::is_white_chessman(figure f, chessman c) const {
    figure t(c, color::white);
    return f == t;
}

bool independent_board::is_attack_each_other(bool is_desired, figure f, chessman c1, chessman c2) const {
    return is_attack_each_other(is_desired, f, c1)
            || is_white_chessman(f, c2);
}

bool independent_board::is_attack_each_other(bool is_desired, figure f, chessman c) const {
    return (is_desired && f.get_color() == color::white)
           || is_white_chessman(f, c);
}

bool independent_board::solution_params(int *figures_count) const {
    for (int i = 0; i < CHESSMAN_TYPES; ++i) {
        if (figures_count[i] != figures_count[i + CHESSMAN_TYPES]) {
            return false;
        }
    }
    return true;
}

}