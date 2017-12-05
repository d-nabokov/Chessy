#include "gtest/gtest.h"
#include "../src/io_interface.h"
#include "../src/solver.h"
#include <memory>

namespace {

using chessy::solver;
chessy::io_interface i;

std::vector<solver::i_solution> get_solutions(int size, const std::string &filename) {
    chessy::solver s(size);
    return s.solve(i.parse("../test/data/" + filename));
}

void assert_solutions_size(int board_size, const std::string &filename, int solutions_size) {
    auto solutions = get_solutions(board_size, filename);
    ASSERT_EQ(solutions_size, solutions.size());
}

namespace board3x3 {

TEST(board3x3, test1) {
    assert_solutions_size(3, "3x3/001", 2);
}

TEST(board3x3, test2) {
    assert_solutions_size(3, "3x3/002", 0);
}

TEST(board3x3, test3) {
    assert_solutions_size(3, "3x3/003", 1);
}

TEST(board3x3, test4) {
    assert_solutions_size(3, "3x3/004", 0);
}

TEST(board3x3, test5) {
    assert_solutions_size(3, "3x3/005", 2);
}

TEST(board3x3, test6) {
    assert_solutions_size(3, "3x3/006", 0);
}

TEST(board3x3, test7) {
    assert_solutions_size(3, "3x3/007", 2);
}

TEST(board3x3, test8) {
    assert_solutions_size(3, "3x3/008", 0);
}

TEST(board3x3, test9) {
    assert_solutions_size(3, "3x3/009", 1);
}

TEST(board3x3, test10) {
    assert_solutions_size(3, "3x3/010", 0);
}

TEST(board3x3, test11) {
    assert_solutions_size(3, "3x3/011", 1);
}

TEST(board3x3, test12) {
    assert_solutions_size(3, "3x3/012", 0);
}

TEST(board3x3, test13) {
    assert_solutions_size(3, "3x3/013", 1);
}


} // board3x3 namespace

namespace queens {

TEST(queens, test1) {
    assert_solutions_size(5, "queens/001", 2);
}

TEST(queens, test2) {
    assert_solutions_size(6, "queens/002", 1);
}

TEST(queens, test3) {
    assert_solutions_size(7, "queens/003", 6);
}

TEST(queens, test4) {
    assert_solutions_size(8, "queens/004", 12);
}

} // queens namespace

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}