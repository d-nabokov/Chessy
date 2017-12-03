#include "gtest/gtest.h"
#include "../src/superclass.cpp"

namespace {

TEST(board3x3, kek1) {
    chessy::parse("test/data/3x3/001");
    std::vector<chessy::i_solution> solutions = chessy::solve();
    ASSERT_EQ(2, solutions.size());
}

TEST(board3x3, kek2) {
    chessy::parse("test/data/3x3/002");
    std::vector<chessy::i_solution> solutions = chessy::solve();
    ASSERT_EQ(0, solutions.size());
}

//TEST(board3x3AAA, kek3) {
//    chessy::parse("../test/data/3x3/003");
//    std::vector<chessy::i_solution> solutions = chessy::solve();
//    ASSERT_EQ(1, solutions.size());
//}

//TEST(board3x3, kek4) {
//    chessy::parse("../test/data/3x3/004");
//    std::vector<chessy::i_solution> solutions = chessy::solve();
//    ASSERT_EQ(0, solutions.size());
//}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}