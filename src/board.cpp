//#include <cstring>
//#include <cstdlib>
//#include <algorithm>
//#include "board.h"
//
//namespace chessy {
//
//board::board(int size)
//        : horizontal(new bool[size]), vertical(new bool[size]),
//          asc_diagonal(new bool[2 * size - 1]), desc_diagonal(new bool[2 * size - 1]),
//          size_(size)
//{
//    field = new chessman*[size];
//    for (int i = 0; i < size; ++i) {
//        field[i] = new chessman[size];
//    }
//    reset();
//}
//
//board::~board() {
//    for (int i = 0; i < size_; ++i) {
//        delete[] field[i];
//    }
//    delete[] field;
//    delete[] horizontal;
//    delete[] vertical;
//    delete[] asc_diagonal;
//    delete[] desc_diagonal;
//}
//
//void board::reset() {
//    for (int i = 0; i < size_; ++i) {
//        std::memset(field[i], static_cast<int>(chessman::empty), size_ * sizeof(**field));
//    }
//    std::memset(horizontal, 0, size_ * sizeof(*horizontal));
//    std::memset(vertical, 0, size_ * sizeof(*vertical));
//    std::memset(asc_diagonal, 0, (2 * size_ - 1) * sizeof(*asc_diagonal));
//    std::memset(desc_diagonal, 0, (2 * size_ - 1) * sizeof(*desc_diagonal));
//}
//
//bool board::check_chessman(int x, int y, chessman f, int *figures) const {
//
//}
//
//void board::set_chessman(int x, int y, chessman f) {
//
//}
//
//void board::unset_chessman(int x, int y, chessman f) {
//
//}
//
//}