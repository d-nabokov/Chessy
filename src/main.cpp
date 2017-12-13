#include <iostream>
#include <fstream>
#include "io_interface.h"
#include "solver.h"
#include "boards.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: <input_file> <output_file> [size]\n";
        return 1;
    }

    int size = argc > 3 ? static_cast<int>(std::stoul(argv[3])) : 3;
    chessy::io_interface i;
    auto pair = i.parse(argv[1]);
    chessy::board *b;
    switch (pair.second) {
        case modes::independent_colorless:
            b = new chessy::colorless_independent_board(size);
            break;
        case modes::independent:
            b = new chessy::independent_board(size);
            break;
        case modes::dominant:
            b = new chessy::dominant_board(size);
            break;
    }
    std::shared_ptr<chessy::board> shr(b);
    chessy::solver solver(shr);
    auto solutions = solver.solve_not_fundamental(pair.first);
//    auto solutions = solver.solve(pair.first);

    std::ofstream of(argv[2]);

    for (const auto &s : solutions) {
        i.print_solution(of, s, pair.second == modes::independent);
    }

    return 0;
}