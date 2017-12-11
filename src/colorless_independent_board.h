#ifndef CHESSY_COLORLESS_BOARD_H
#define CHESSY_COLORLESS_BOARD_H

#include "board.h"

namespace chessy {

class colorless_independent_board : public board {
    bool *horizontal;
    bool *vertical;
    bool *asc_diagonal;
    bool *desc_diagonal;
public:
    colorless_independent_board(int size);
    ~colorless_independent_board() override;

    void reset() override;

    bool check_chessman(int x, int y, figure f, int *figures) const override;

    void set_chessman(int x, int y, figure f) override;

    void unset_chessman(int x, int y, figure f) override;

    bool solution_params() override;

    i_solution get_solution() override;
};


}



#endif //CHESSY_COLORLESS_BOARD_H
