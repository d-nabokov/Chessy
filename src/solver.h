#ifndef CHESSY_SOLVER_H
#define CHESSY_SOLVER_H

#include <vector>
#include <iostream>
#include "chessman.h"
#include "board.h"
#include "solution.h"

class solver {
    int size_;
    chessy::board board_checker_;
    int indexes[chessy::CHESSMAN_TYPES];
public:
    using chessy::chessman;
    using chessy::i_solution;

    solver(int size)
        : size_(size), board_checker_(size)
    {
    }

    ~solver() = default;

    unsigned long long int recursive_count = 0;

    std::vector<i_solution> solve(const std::shared_ptr<int> &f) {
        reset();

        int *figures = f.get();
        int sum = 0;
        for (int i = 0; i < chessy::CHESSMAN_TYPES; ++i) {
            sum += figures[i];
            indexes[i] = sum;
        }

        std::vector<i_solution> solutions;
        if (sum != 0) {
            recursive_solve(&solutions, 0);
        }
        std::cout << "SOLUTIONS SIZE BEFORE = " << solutions.size() << "\n";
        solutions = i_solution::remove_duplicates(&solutions);
        std::cout << "SOLUTIONS SIZE AFTER = " << solutions.size() << "\n";
        std::cout << "RECURSIVE CALLS = " << recursive_count << "\n";
        return solutions;
    }

private:
    void reset() {
        std::memset(indexes, 0, chessy::CHESSMAN_TYPES * sizeof(*indexes));
        board_checker_.reset();
    }

    void recursive_solve(std::vector<i_solution> *solutions, int f_number) {
        ++recursive_count;
        // TODO сделать условием "f_number == chessman_count() - 1" и не делать одну рекурсию лишнюю
        if (f_number == chessman_count()) {
            solutions->push_back(i_solution::get_solution(field, size_));
            return;
        }

//    print_debug();

        // TODO передавать предыдущую фигуру и её вертикальную координату. Если фигуры совпадают, то новую ставим не выше предыдущей

        // TODO передавать index ??
        int chessman_index = 0;
        while (indexes[chessman_index] <= f_number) {
            ++chessman_index;
        }
        chessman f = chessy::chessman_from_index(chessman_index);
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                if (check_chessman(i, j, f)) {
                    set_chessman(i, j, f);
                    recursive_solve(solutions, f_number + 1);
                    unset_chessman(i, j, f);
                }
            }
        }
    }

    int chessman_count() {
        return indexes[chessy::CHESSMAN_TYPES - 1];
    }
};


#endif //CHESSY_SOLVER_H
