#ifndef CHESSY_DOMINANT_BOARD_H
#define CHESSY_DOMINANT_BOARD_H

#include "board.h"

namespace chessy {

class dominant_board : public board {
public:
    dominant_board(int size);

    ~dominant_board() override;

    void reset() override;

    bool check_chessman(int x, int y, figure f, int *figures) const override;

    void set_chessman(int x, int y, figure f) override;

    void unset_chessman(int x, int y, figure f) override;

    bool solution_params(int *figures_count) const override;
};

}

#endif //CHESSY_DOMINANT_BOARD_H
