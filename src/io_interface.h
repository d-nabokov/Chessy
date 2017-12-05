#ifndef CHESSY_PARSER_H
#define CHESSY_PARSER_H

#include "chessman.h"
#include "solution.h"
#include <memory>

namespace chessy {

class io_interface {
public:
    std::shared_ptr<int> parse(const std::string &filename) const;
    void print_solution(std::ostream &os, const solution<int> &s) const;
//    void print_debug() const;

private:
    chessman chessman_from_char(char c) const;
    std::string chessman_out(chessman f) const;
};

}

#endif //CHESSY_PARSER_H
