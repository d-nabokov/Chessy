#include <iostream>
#include <memory>
#include "io_interface.h"
#include "solver.h"
#include "board.h"
#include "colorless_independent_board.h"
#include "independent_board.h"


int main(int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cout << "Usage: <input_file> <output_file> [size]\n";
//    }
    int size = 3;
    chessy::io_interface i;
    auto pair = i.parse("../src/input");
    chessy::board *b;
    switch (pair.second) {
        case modes::independent_colorless:
            b = new chessy::colorless_independent_board(size);
            break;
        case modes::independent:
            std::cout << "COLORFUL!!\n";
            b = new chessy::independent_board(size);
            break;
    }
    std::shared_ptr<chessy::board> shr(b);
    chessy::solver solver(shr);
//    auto solutions = solver.solve(pair.first);
    auto solutions = solver.solve_not_fundamental(pair.first);

    for (const auto &s : solutions) {
        i.print_solution(std::cout, s, pair.second == modes::independent);
    }


    return 0;
}