#ifndef CHESSY_PARSER_H
#define CHESSY_PARSER_H

#include "chessman.h"
#include "solution.h"
#include "modes.h"
#include <memory>

namespace chessy {

class io_interface {
public:
    using i_solution = solution<int>;
    using i_shared_ptr = std::shared_ptr<int>;

    std::pair<i_shared_ptr, modes> parse(const std::string &filename) const;
    void print_solution(std::ostream &os, const i_solution &s, bool colored) const;
//    void print_debug() const;

private:
    chessman chessman_from_char(char c) const;
    color color_from_char(char c) const;
    std::string figure_out(figure f, bool colored) const;
};

}

#endif //CHESSY_PARSER_H
