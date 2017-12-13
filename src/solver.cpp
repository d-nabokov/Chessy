#include "solver.h"
#include <cstring>

namespace chessy {

solver::solver(const std::shared_ptr<board> &b)
        : board_(b)
{
    size_ = board_->get_size();
}

std::vector<solver::i_solution> solver::solve(const i_shared_ptr &f) {
    auto solutions = solve_not_fundamental(f);
    solutions = i_solution::remove_duplicates(&solutions, board_->solution_params(f.get()));
    return solutions;
}

std::vector<solver::i_solution> solver::solve_not_fundamental(const i_shared_ptr &f) {
    reset();

    int *figures_count = f.get();
    board_->init(figures_count);

    std::vector<solver::i_solution> solutions;
    recursive_solve(&solutions, 0, figures_count, 0, 0, -1);
    return solutions;
}

void solver::reset() {
    board_->reset();
}

void solver::recursive_solve(std::vector<solver::i_solution> *solutions, int f_number, int *figures_count, int prev_index, int prev_x, int prev_y) {
    if (f_number == board_->figure_count()) {
        auto s = board_->get_solution();
        if (!s.empty()) {
            solutions->push_back(std::move(s));
        }
        return;
    }

    int chessman_index = board_->get_next_index(prev_index, f_number);

    figure f = figure::figure_from_index(chessman_index);
    bool first_iteration = true;
    int j, i = (prev_index == chessman_index) ? prev_x : 0;
    for (; i < size_; ++i) {
        if (first_iteration) {
            first_iteration = false;
            j = (prev_index == chessman_index) ? prev_y + 1 : 0;
        } else {
            j = 0;
        }
        for (; j < size_; ++j) {
            if (board_->check_chessman(i, j, f, figures_count)) {
                board_->set_chessman(i, j, f);
                recursive_solve(solutions, f_number + 1, figures_count, chessman_index, i, j);
                board_->unset_chessman(i, j, f);
            }
        }
    }
}

}