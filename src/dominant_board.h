#ifndef CHESSY_DOMINANT_BOARD_H
#define CHESSY_DOMINANT_BOARD_H

#include "board.h"

namespace chessy {

class dominant_board : public board {
    int **cover_field_;
    int uncovered_;
    int potential_;
public:
    dominant_board(int size);

    ~dominant_board() override;

    void reset() override;

    bool check_chessman(int x, int y, figure f, int *figures_count) const override;

    void set_chessman(int x, int y, figure f) override;

    void unset_chessman(int x, int y, figure f) override;

    bool solution_params(int *figures_count) const override;

    void init(int *figures_count) override;

    i_solution get_solution() override;

private:
    int max_weight(figure f) const;
    int even_size() const;
    void cover(int &cell);
    void uncover(int &cell);
    void mark_figure(int x, int y, figure f, void (dominant_board::*func)(int &cell));
};

}

#endif //CHESSY_DOMINANT_BOARD_H
