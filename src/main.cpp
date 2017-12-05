#include <iostream>
#include <memory>
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

    std::cout << "SOLUTIONS = " << solutions.size() << "\n";

//    chessy::parse("../src/input");
//    std::vector<chessy::i_solution> solutions = chessy::solve();
//    for (const auto &s : solutions) {
//        std::cout << s << "\n";
//    }

    return 0;
}