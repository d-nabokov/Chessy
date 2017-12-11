#include "gtest/gtest.h"
#include "../src/io_interface.h"
#include "../src/solver.h"
#include "../src/colorless_independent_board.h"
#include "../src/independent_board.h"
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

template <class B>
class solutions_helper {
public:
    static std::vector<solver::i_solution> get_solutions(int size, const std::string &filename, bool fundamental) {
        chessy::solver s(std::shared_ptr<chessy::board>(new B(size)));
        if (fundamental) {
            return s.solve(i.parse("../test/data/" + filename).first);
        } else {
            return s.solve_not_fundamental(i.parse("../test/data/" + filename).first);
        }
    }

    static void assert_solutions_size(int board_size, const std::string &filename, int solutions_size) {
        auto solutions = get_solutions(board_size, filename, true);
        ASSERT_EQ(solutions_size, solutions.size());
    }

    static void assert_not_fundamental_solutions_size(int board_size, const std::string &filename, int solutions_size) {
        auto solutions = get_solutions(board_size, filename, false);
        ASSERT_EQ(solutions_size, solutions.size());
    }
};

using cib = solutions_helper<chessy::colorless_independent_board>;
using ib = solutions_helper<chessy::independent_board>;


namespace board3x3 {

TEST(board3x3, test1) {
    int solutions[] = {2, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0, 1};
    for (int i = 1; i < 14; ++i) {
        cib::assert_solutions_size(3, "3x3/" + test_name(i), solutions[i - 1]);
    }
}


} // board3x3 namespace

namespace queens {

TEST(queens, test1) {
    int solutions[] = {2, 1, 6, 12};
    for (int i = 1; i < 4; ++i) {
        int n = i + 4;
        cib::assert_solutions_size(n, "queens/" + test_name(i), solutions[i - 1]);
    }
}

} // queens namespace

namespace rooks {

TEST(rooks, test1) {
    for (int i = 1; i < 4; ++i) {
        int n = i + 4;
        cib::assert_not_fundamental_solutions_size(n, "rooks/" + test_name(i), factorial(n));
    }
}

} // rooks namespace

namespace colorful {

TEST(colorful, test1) {
    ib::assert_solutions_size(3, "colorful/" + test_name(1), 4);
    ib::assert_not_fundamental_solutions_size(3, "colorful/" + test_name(1), 9 * 8 / 2);
}

TEST(colorful, test2) {
    ib::assert_solutions_size(3, "colorful/" + test_name(2), 3);
    ib::assert_not_fundamental_solutions_size(3, "colorful/" + test_name(2), 18);
}

} // colorful namespace

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}