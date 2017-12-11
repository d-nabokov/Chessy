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

enum class color : unsigned char {
    white = 0x0,
    black = 0x80
};

static const int CHESSMAN_TYPES = 6;

constexpr int chessman_index(chessman f) {
    return static_cast<int>(f) - 1;
}

class figure {
    unsigned char f_;

    static const unsigned char CHESSMAN_MASK = 0x7f;
    static const unsigned char COLOR_MASK = ~CHESSMAN_MASK;

    figure(unsigned char f) {
        f_ = f;
    }

public:
    figure(chessman f) {
        f_ = static_cast<unsigned char>(f);
    }

    figure(chessman f, color c) {
        f_ = static_cast<unsigned char>(f) | static_cast<unsigned char>(c);
    }

    figure() = default;

    constexpr int figure_index() const {
        return (f_ & CHESSMAN_MASK) + (CHESSMAN_TYPES * (get_color() == color::black ? 1 : 0)) - 1;
    }

    static figure figure_from_index(int i) {
        unsigned char color_bits = static_cast<unsigned char>((i / CHESSMAN_TYPES) == 0 ? color::white : color::black);
        return figure(((i % CHESSMAN_TYPES) + 1) | color_bits);
    }

    bool operator==(chessman other) const {
        return get_chessman() == other;
    }

    bool operator!=(chessman other) const {
        return !(*this == other);
    }

    bool operator==(figure other) const {
        return f_ == other.f_;
    }

    bool operator!=(figure other) const {
        return !(*this == other);
    }

    bool opposite_colors(figure other) const {
        return (f_ ^ COLOR_MASK) == other.f_;
    }

    constexpr color get_color() const {
        return static_cast<color>(f_ & COLOR_MASK);
    }

    constexpr chessman get_chessman() const {
        return static_cast<chessman>(f_ & CHESSMAN_MASK);
    }
};

}

#endif //CHESSY_CHESSMAN_H
