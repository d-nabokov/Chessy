#include <iostream>
#include "io_interface.h"
#include "solver.h"


int main(int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cout << "Usage: <input_file> <output_file> [size]\n";
//    }
    int size = 4;
    chessy::io_interface i;
    auto figures = i.parse("../src/input");
    chessy::solver s(size);
    auto solutions = s.solve(figures);

    for (const auto &s : solutions) {
        i.print_solution(std::cout, s);
    }


    return 0;
}