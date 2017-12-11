#include "dominant_board.h"

namespace chessy {

dominant_board::dominant_board(int size)
        : board(size, CHESSMAN_TYPES)
{
}

dominant_board::~dominant_board() {

}

void dominant_board::reset() {
    board::reset();
}

bool dominant_board::check_chessman(int x, int y, figure f, int *figures) const {
    return false;
}

void dominant_board::set_chessman(int x, int y, figure f) {

}

void dominant_board::unset_chessman(int x, int y, figure f) {

}

bool dominant_board::solution_params(int *figures_count) {
    return false;
}

}