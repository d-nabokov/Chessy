#include <iostream>
#include <memory>
#include "io_interface.h"
#include "solver.h"
#include "colorless_independent_board.h"


int main(int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cout << "Usage: <input_file> <output_file> [size]\n";
//    }
    int size = 8;
    chessy::io_interface i;
    auto figures = i.parse("../src/input");
    std::shared_ptr<chessy::board> b(new chessy::colorless_independent_board(size));
    chessy::solver solver(b);
    auto solutions = solver.solve_not_fundamental(figures);

//    for (const auto &s : solutions) {
//        i.print_solution(std::cout, s);
//    }


    return 0;
}