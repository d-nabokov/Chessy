#include "board_checker.h"

namespace chessy {

board_checker::board_checker(int size)
        : horizontal(new bool[size]), vertical(new bool[size]),
          asc_diagonal(new bool[2 * size - 1]), desc_diagonal(new bool[2 * size - 1]),
          size_(size) {
    reset();
}

~board_checker() {
    delete[] horizontal;
    delete[] vertical;
    delete[] asc_diagonal;
    delete[] desc_diagonal;
}

}