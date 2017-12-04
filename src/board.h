#ifndef CHESSY_BOARD_CHECKER_H
#define CHESSY_BOARD_CHECKER_H

#include "chessman.h"

namespace chessy {

class board {
    chessman **field;
    bool *horizontal;
    bool *vertical;
    bool *asc_diagonal;
    bool *desc_diagonal;
    const int size_;
public:
    using chessy::chessman;

    board(int size);
    ~board();

    void reset();
    bool check_chessman(int x, int y, chessman f) const;

    void set_chessman(int x, int y, chessman f);
    void unset_chessman(int x, int y, chessman f);

private:
    constexpr int asc_index(int x, int y) const;
    constexpr int desc_index(int x, int y) const;
};

}


#endif //CHESSY_BOARD_CHECKER_H
