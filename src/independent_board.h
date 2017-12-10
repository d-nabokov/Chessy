#ifndef CHESSY_INDEPENDENT_BOARD_H
#define CHESSY_INDEPENDENT_BOARD_H

#include "board.h"

namespace chessy {

class independent_board : public board {
public:
    independent_board(int size);

    ~independent_board() override;

    void reset() override;

    bool check_chessman(int x, int y, figure f, int *figures) const override;

    void set_chessman(int x, int y, figure f) override;

    void unset_chessman(int x, int y, figure f) override;

    i_solution get_solution() override;

private:
    bool has_figure(int *figures, chessman c) const;
    bool is_white_chessman(figure f, chessman c) const;
    bool is_attack_each_other(bool is_desired, figure f, chessman c) const;
    bool is_attack_each_other(bool is_desired, figure f, chessman c1, chessman c2) const;
};

}

#endif //CHESSY_INDEPENDENT_BOARD_H