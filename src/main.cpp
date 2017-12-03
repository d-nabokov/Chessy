#include "superclass.cpp"


int main() {
    chessy::parse("../src/input");
    std::vector<chessy::i_solution> solutions = chessy::solve();
    for (const auto &s : solutions) {
        std::cout << s << "\n";
    }

    return 0;
}