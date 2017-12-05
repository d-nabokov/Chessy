#include "solver.h"
#include <cstring>

namespace chessy {

solver::solver(int size)
        : size_(size), board_(size) {
}

unsigned long long int recursive_count = 0;

std::vector<solver::i_solution> solver::solve(const std::shared_ptr<int> &f) {
    reset();

    int *figures = f.get();
    int sum = 0;
    for (int i = 0; i < CHESSMAN_TYPES; ++i) {
        sum += figures[i];
        indexes[i] = sum;
    }

    chessman_count_ = chessman_count();

    std::vector<solver::i_solution> solutions;
    if (sum != 0) {
        recursive_solve(&solutions, 0, figures, 0, 0);
    }
    std::cout << "SOLUTIONS SIZE BEFORE = " << solutions.size() << "\n";
    solutions = i_solution::remove_duplicates(&solutions);
    std::cout << "SOLUTIONS SIZE AFTER = " << solutions.size() << "\n";
    std::cout << "RECURSIVE CALLS = " << recursive_count << "\n";
    return solutions;
}

void solver::reset() {
    std::memset(indexes, 0, CHESSMAN_TYPES * sizeof(*indexes));
    board_.reset();
}

void solver::recursive_solve(std::vector<solver::i_solution> *solutions, int f_number, int *figures, int prev_index, int prev_x) {
    ++recursive_count;
    // TODO сделать условием "f_number == chessman_count() - 1" и не делать одну рекурсию лишнюю
    if (f_number == chessman_count_) {
        solutions->push_back(solver::i_solution::get_solution(board_.get_field(), size_));
        return;
    }

//    print_debug();

    // TODO передавать предыдущую фигуру и её вертикальную координату. Если фигуры совпадают, то новую ставим не выше предыдущей

    // TODO передавать index ??
    int chessman_index = prev_index;
    while (indexes[chessman_index] <= f_number) {
        ++chessman_index;
    }
    chessman f = chessman_from_index(chessman_index);
    int i = (prev_index == chessman_index) ? prev_x : 0;
    for (; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            if (board_.check_chessman(i, j, f, figures)) {
                board_.set_chessman(i, j, f);
                recursive_solve(solutions, f_number + 1, figures, chessman_index, i);
                board_.unset_chessman(i, j, f);
            }
        }
    }
}

int solver::chessman_count() {
    return indexes[CHESSMAN_TYPES - 1];
}

}