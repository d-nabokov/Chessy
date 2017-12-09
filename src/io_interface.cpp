#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

#include "io_interface.h"

namespace chessy {

io_interface::i_shared_ptr io_interface::parse(const std::string &filename) const {
    i_shared_ptr f(new int[CHESSMAN_TYPES], std::default_delete<int[]>());
    int * figures = f.get();
    std::memset(figures, 0, CHESSMAN_TYPES * sizeof(*figures));

    std::ifstream in(filename);
    if (!in) {
        throw std::invalid_argument("File does not exist");
    }
    for (std::string line; std::getline(in, line);) {
        if (line.size() == 0) {
            continue;
        }
        std::istringstream ss(line);
        std::string s;
        ss >> s;

        int count = 1;
        auto index = s.find('*');
        if (index != std::string::npos) {
            count = static_cast<int>(std::stoul(s.substr(0, index)));
            s = s.substr(index + 1);
        }
        if (s.size() != 1) {
            throw std::invalid_argument("Invalid figure");
        }

        chessman figure = chessman_from_char(s[0]);
        figures[chessman_index(figure)] += count;
    }
    return f;
}

//void io_interface::print_debug(const chessman **field, int size) const {
//    std::cout << "*****START*****\n";
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            std::cout << chessman_out(field[i][j]) << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "**\n";
//    for (int i = 0; i < size; ++i) {
//        std::cout << horizontal[i] << " ";
//    }
//    std::cout << "\n";
//    for (int i = 0; i < size; ++i) {
//        std::cout << vertical[i] << " ";
//    }
//    std::cout << "\n";
//    for (int i = 0; i < 2 * size - 1; ++i) {
//        std::cout << asc_diagonal[i] << " ";
//    }
//    std::cout << "\n";
//    for (int i = 0; i < 2 * size - 1; ++i) {
//        std::cout << desc_diagonal[i] << " ";
//    }
//    std::cout << "\n";
//    std::cout << "*****END*****" << std::endl;
//}

chessman io_interface::chessman_from_char(char c) const {
    switch (c) {
        case 'Q':
        case 'q':
            return chessman::queen;
        case 'R':
        case 'r':
            return chessman::rook;
        case 'B':
        case 'b':
            return chessman::bishop;
        case 'N':
        case 'n':
            return chessman::knight;
        case 'K':
        case 'k':
            return chessman::king;
        case 'P':
        case 'p':
            return chessman::pawn;
        default:
            throw std::logic_error("No such figure");
    }
}

std::string io_interface::chessman_out(chessman f) const {
    switch (f) {
        case chessman::queen:
            return "Q";
        case chessman::rook:
            return "R";
        case chessman::bishop:
            return "B";
        case chessman::knight:
            return "N";
        case chessman::king:
            return "K";
        case chessman::pawn:
            return "P";
        case chessman::empty:
            return "-";
    }
}

void io_interface::print_solution(std::ostream &os, const solution<int> &s) const {
    i_solution::map_t v = s.get_figures();
    const int size = s.get_size();
    i_solution::map_t::const_iterator end = v.end();
    i_solution::map_t::iterator it;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((it = v.find(std::make_pair(i, j))) != end) {
                os << chessman_out(it->second);
            } else {
                os << '-';
            }
        }
        os << "\n";
    }
    os << "\n";
}

}