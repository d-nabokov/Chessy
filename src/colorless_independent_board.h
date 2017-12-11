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

    bool check_chessman(int x, int y, figure f, int *figures_count) const override;

    void set_chessman(int x, int y, figure f) override;

    void unset_chessman(int x, int y, figure f) override;

    bool solution_params(int *figures_count) const override;

private:
    bool has_figure(int *figures_count, chessman c) const;
};

}



#endif //CHESSY_COLORLESS_BOARD_H
