#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

#include "io_interface.h"

namespace chessy {

std::pair<io_interface::i_shared_ptr, modes> io_interface::parse(const std::string &filename) const {
    i_shared_ptr ret;
    int * figures;

    std::ifstream in(filename);
    if (!in) {
        throw std::invalid_argument("File does not exist");
    }

    bool first_line = true;
    modes m = modes::independent_colorless;
    for (std::string line; std::getline(in, line);) {
        if (line.size() == 0) {
            continue;
        }

        if (first_line && line[0] == 'd') {
            m = modes::dominant;
            continue;
        }

        int count = 1;
        auto index = line.find('*');
        if (index != std::string::npos) {
            count = static_cast<int>(std::stoul(line.substr(0, index)));
            line = line.substr(index + 1);
        }

        auto l_size = line.size();

        if (first_line) {
            first_line = false;
            int size;
            if (l_size >= 3 && m == modes::independent_colorless) {
                m = modes::independent;
                size = 2 * CHESSMAN_TYPES;
            } else {
                size = CHESSMAN_TYPES;
            }

            ret = i_shared_ptr(new int[size], std::default_delete<int[]>());
            figures = ret.get();
            std::memset(figures, 0, size * sizeof(*figures));
        }

        if (m == modes::independent && l_size < 3) {
            throw std::invalid_argument("Invalid line");
        }

        chessman c = chessman_from_char(line[0]);
        figure f = m == modes::independent ? figure(c, color_from_char(line[2])) : figure(c);
        figures[f.figure_index()] += count;
    }
    return std::make_pair(ret, m);
}

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
            throw std::invalid_argument("No such figure");
    }
}

color io_interface::color_from_char(char c) const {
    switch (c) {
        case 'W':
        case 'w':
            return color::white;
        case 'B':
        case 'b':
            return color::black;
        default:
            throw std::invalid_argument("No such color");
    }
}

std::string io_interface::figure_out(figure f, bool colored) const {
    std::string s;
    switch (f.get_chessman()) {
        case chessman::queen:
            s += 'Q';
            break;
        case chessman::rook:
            s += 'R';
            break;
        case chessman::bishop:
            s += 'B';
            break;
        case chessman::knight:
            s += 'N';
            break;
        case chessman::king:
            s += 'K';
            break;
        case chessman::pawn:
            s += 'P';
            break;
        case chessman::empty:
            s += '_';
    }

    if (colored) {
        switch (f.get_color()) {
            case color::white:
                s += 'w';
                break;
            case color::black:
                s += 'b';
                break;
        }
    }
    return s;
}

void io_interface::print_solution(std::ostream &os, const solution<int> &s, bool colored) const {
    i_solution::map_t v = s.get_figures();
    const int size = s.get_size();
    i_solution::map_t::const_iterator end = v.end();
    i_solution::map_t::iterator it;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((it = v.find(std::make_pair(i, j))) != end) {
                os << figure_out(it->second, colored);
            } else {
                os << '-';
                if (colored) {
                    os << ' ';
                }
            }
        }
        os << '\n';
    }
    os << '\n';
}

}