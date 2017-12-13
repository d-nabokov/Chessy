#ifndef CHESSY_SOLVER_H
#define CHESSY_SOLVER_H

#include <vector>
#include <memory>
#include "chessman.h"
#include "boards.h"
#include "solution.h"

namespace chessy {

class solver {
    int size_;
    std::shared_ptr<board> board_;
public:
    using i_solution = solution<int>;
    using i_shared_ptr = std::shared_ptr<int>;

    solver(const std::shared_ptr<board> &b);

    ~solver() = default;

    std::vector<i_solution> solve(const i_shared_ptr &f);
    std::vector<i_solution> solve_not_fundamental(const i_shared_ptr &f);

private:
    void reset();

    void recursive_solve(std::vector<i_solution> *solutions, int f_number, int *figures_count, int prev_index, int prev_x, int prev_y);
};

}


#endif //CHESSY_SOLVER_H
