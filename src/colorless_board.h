#ifndef CHESSY_COLORLESS_BOARD_H
#define CHESSY_COLORLESS_BOARD_H

#include "board.h"

namespace chessy {

class colorless_board : board {
    bool *horizontal;
    bool *vertical;
    bool *asc_diagonal;
    bool *desc_diagonal;
public:
    colorless_board(int size);
    ~colorless_board() override;

    void reset() override;

    bool check_chessman(int x, int y, chessman f, int *figures) const override;

    void set_chessman(int x, int y, chessman f) override;

    void unset_chessman(int x, int y, chessman f) override;

    i_solution get_solution() override;

};


}



#endif //CHESSY_COLORLESS_BOARD_H
