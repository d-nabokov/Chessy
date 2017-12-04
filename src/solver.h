#ifndef CHESSY_SOLVER_H
#define CHESSY_SOLVER_H

#include "chessman.h"
#include "board_checker.h"

class solver {
    int size_;
    chessman **field;
    chessy::board_checker board_checker_;
public:
    using chessy::chessman;
    solver(int size)
        : size_(size), board_checker_(size)
    {
        field = new chessman*[size];
        for (int i = 0; i < size; ++i) {
            field[i] = new chessman[size];
            // TODO
            std::memset(field[i], static_cast<int>(chessman::empty), size * sizeof(**field));
        }
    }

    ~solver() {
        for (int i = 0; i < size; ++i) {
            delete[] field[i];
        }
        delete[] field;
    }


    unsigned long long int recursive_count = 0;

    std::vector<i_solution> solve(const std::shared_ptr<int> &f) {
        int *figures = figures.get();
        int sum = 0;
        for (int i = 0; i < CHESSMAN_TYPES; ++i) {
            sum += figures[i];
            indexes[i] = sum;
        }

        std::vector<i_solution> solutions;
        if (sum != 0) {
            recursive_solve(&solutions, 0);
        }
        cout << "SOLUTIONS SIZE BEFORE = " << solutions.size() << "\n";
        solutions = i_solution::remove_duplicates(&solutions);
        cout << "SOLUTIONS SIZE AFTER = " << solutions.size() << "\n";
        cout << "RECURSIVE CALLS = " << recursive_count << "\n";
        return solutions;
    }

    void recursive_solve(std::vector<i_solution> *solutions, int f_number) {
        ++recursive_count;
        // TODO сделать условием "f_number == chessman_count() - 1" и не делать одну рекурсию лишнюю
        if (f_number == chessman_count()) {
            solutions->push_back(get_solution());
            return;
        }

//    print_debug();

        // TODO передавать предыдущую фигуру и её вертикальную координату. Если фигуры совпадают, то новую ставим не выше предыдущей

        // TODO передавать index ??
        int chessman_index = 0;
        while (indexes[chessman_index] <= f_number) {
            ++chessman_index;
        }
        chessman f = chessman_from_index(chessman_index);
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (check_chessman(i, j, f)) {
                    set_chessman(i, j, f);
                    recursive_solve(solutions, f_number + 1);
                    unset_chessman(i, j, f);
                }
            }
        }
    }

    i_solution get_solution() {
        i_solution s;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (field[i][j] != chessman::empty) {
                    s.add_figure(i, j, field[i][j]);
                }
            }
        }
        return s;
    }

    void set_chessman(int x, int y, chessman f) {
        field[x][y] = f;
        if (f == chessman::queen || f == chessman::rook) {
            horizontal[x] = true;
            vertical[y] = true;
        }

        if (f == chessman::queen || f == chessman::bishop) {
            asc_diagonal[asc_index(x, y)] = true;
            desc_diagonal[desc_index(x, y)] = true;
        }
    }

    void unset_chessman(int x, int y, chessman f) {
        field[x][y] = chessman::empty;
        if (f == chessman::queen || f == chessman::rook) {
            horizontal[x] = false;
            vertical[y] = false;
        }

        if (f == chessman::queen || f == chessman::bishop) {
            asc_diagonal[asc_index(x, y)] = false;
            desc_diagonal[desc_index(x, y)] = false;
        }
    }
};


#endif //CHESSY_SOLVER_H
