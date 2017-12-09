#include "gtest/gtest.h"
#include "../src/io_interface.h"
#include "../src/solver.h"
#include "../src/colorless_board.h"
#include <memory>
#include <string>

namespace {

std::string test_name(unsigned n) {
    if (n >= 1000) {
        return "";
    }
    char buf[4];
    sprintf(buf, "%03d", n);
    buf[3] = '\0';
    return buf;
}

int factorial(int n) {
    int ret = 1;
    for (int i = n; i > 1; --i) {
        ret *= i;
    }
    return ret;
}

using chessy::solver;
chessy::io_interface i;

std::vector<solver::i_solution> get_solutions(int size, const std::string &filename, bool fundamental) {
    chessy::solver s(std::shared_ptr<chessy::board>(new chessy::colorless_board(size)));
    if (fundamental) {
        return s.solve(i.parse("../test/data/" + filename));
    } else {
        return s.solve_not_fundamental(i.parse("../test/data/" + filename));
    }
}

void assert_solutions_size(int board_size, const std::string &filename, int solutions_size) {
    auto solutions = get_solutions(board_size, filename, true);
    ASSERT_EQ(solutions_size, solutions.size());
}

void assert_not_fundamental_solutions_size(int board_size, const std::string &filename, int solutions_size) {
    auto solutions = get_solutions(board_size, filename, false);
    ASSERT_EQ(solutions_size, solutions.size());
}

namespace board3x3 {

TEST(board3x3, test1) {
    int solutions[] = {2, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0, 1};
    for (int i = 1; i < 14; ++i) {
        assert_solutions_size(3, "3x3/" + test_name(i), solutions[i - 1]);
    }
}


} // board3x3 namespace

namespace queens {

TEST(queens, test1) {
    int solutions[] = {2, 1, 6, 12};
    for (int i = 1; i < 4; ++i) {
        int n = i + 4;
        assert_solutions_size(n, "queens/" + test_name(i), solutions[i - 1]);
    }
}

} // queens namespace

namespace rooks {

TEST(rooks, test1) {
    for (int i = 1; i < 4; ++i) {
        int n = i + 4;
        assert_not_fundamental_solutions_size(n, "rooks/" + test_name(i), factorial(n));
    }
}

} // rooks namespace

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}