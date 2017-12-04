#ifndef CHESSY_CHESSMAN_H
#define CHESSY_CHESSMAN_H

namespace chessy {

enum class chessman : unsigned char {
    empty = 0,
    queen,
    rook,
    bishop,
    knight,
    king,
    pawn
};

static const int CHESSMAN_TYPES = 6;

constexpr int chessman_index(chessman f) {
    return static_cast<int>(f) - 1;
}

constexpr chessman chessman_from_index(int i) {
    return static_cast<chessman>(i + 1);
}

}

#endif //CHESSY_CHESSMAN_H
