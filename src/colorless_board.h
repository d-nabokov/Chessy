#ifndef CHESSY_COLORLESS_BOARD_H
#define CHESSY_COLORLESS_BOARD_H

#include "board.h"

namespace chessy {

class colorless_board : public board {
    bool *horizontal;
    bool *vertical;
    bool *asc_diagonal;
    bool *desc_diagonal;
public:
    colorless_board(int size);
    ~colorless_board() override;

    void reset() override;

    bool check_chessman(int x, int y, figure f, int *figures) const override;

    void set_chessman(int x, int y, figure f) override;

    void unset_chessman(int x, int y, figure f) override;

    i_solution get_solution() override;

protected:
    bool has_king(int *figures) const override;

    bool has_knight(int *figures) const override;

    bool has_pawn(int *figures) const override;

};


}



#endif //CHESSY_COLORLESS_BOARD_H
