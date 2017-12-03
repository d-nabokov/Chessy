#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <exception>
#include <vector>
#include <unordered_map>
#include <utility>
#include <list>

using std::cout;
using std::string;
static const int SIZE = 3;

enum class chessman : unsigned char {
    empty = 0,
    queen,
    rook,
    bishop,
    knight,
    king,
    pawn
};

string chessman_out(chessman f) {
    switch(f) {
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
            return "#";
    }
}

unsigned long long int iterations = 0;

template<class C>
class solution {
public:
    solution() = default;
    solution(solution &&other) = default;

    struct pair_hash;
    using coordinate_t = std::pair<C, C>;
    using map_t = std::unordered_map<coordinate_t, chessman, pair_hash>;

    struct pair_hash {
        size_t operator()(const coordinate_t &p) const {
            std::hash<C> h;
            return (h(p.first) << 1) ^ h(p.second);
        }
    };

    void add_figure(const C &x, const C &y, chessman f) {
        m[std::make_pair(x, y)] = f;
    }
    friend std::ostream &operator<<(std::ostream &os, const solution &s) {
        os << "******SOLUTION******\n";
        for (const auto &p : s.m) {
            coordinate_t coord = p.first;
            os << coord.first << " " << coord.second << " " << chessman_out(p.second) << "\n";
        }
        return os;
    }
    bool operator==(const solution &other) const {
        static const int variations_count = 8;
        bool variations[variations_count];
        for (int i = 0; i < variations_count; ++i) {
            variations[i] = true;
        }

        for (const auto &p : m) {
            coordinate_t c = p.first;
            // no transformation
            if (variations[0] && !find_chessman(c.first, c.second, p.second, other)) {
                variations[0] = false;
            }
            // 90 rotation
            if (variations[1] && !find_chessman(SIZE - 1 - c.second, c.first, p.second, other)) {
                variations[1] = false;
            }
            // 180 rotation
            if (variations[2] && !find_chessman(SIZE - 1 - c.first, SIZE - 1 - c.second, p.second, other)) {
                variations[2] = false;
            }
            // 270 rotation
            if (variations[3] && !find_chessman(c.second, SIZE - 1 - c.first, p.second, other)) {
                variations[3] = false;
            }
            // horizontal reflection
            if (variations[4] && !find_chessman(SIZE - 1 - c.first, c.second, p.second, other)) {
                variations[4] = false;
            }
            // vertical reflection
            if (variations[5] && !find_chessman(c.first, SIZE - 1 - c.second, p.second, other)) {
                variations[5] = false;
            }
            // asc diagonal reflection
            if (variations[6] && !find_chessman(SIZE - 1 - c.second, SIZE - 1 - c.first, p.second, other)) {
                variations[6] = false;
            }
            // desc diagonal reflection
            if (variations[7] && !find_chessman(c.second, c.first, p.second, other)) {
                variations[7] = false;
            }
        }
        for (int i = 0; i < variations_count; ++i) {
            if (variations[i]) {
                return true;
            }
        }
        return false;
    }

    static std::vector<solution> remove_duplicates(std::vector<solution> *l) {
        std::vector<bool> dupl(l->size(), false);

        for (int i = 0; i + 1 < l->size(); ++i) {
            if (dupl[i]) {
                continue;
            }
            for (int j = i + 1; j < l->size(); ++j) {
                if ((*l)[i] == (*l)[j]) {
                    dupl[j] = true;
                }
            }
        }

        std::vector<solution> ret;
        for (int i = 0; i < l->size(); ++i) {
            if (!dupl[i]) {
                ret.push_back(std::move((*l)[i]));
            }
        }

        return ret;

    }

private:
    map_t m;

    bool find_chessman(const C &x, const C &y, chessman f, const solution &other) const {
        auto it = other.m.find(std::make_pair(x, y));
        return !((it == other.m.end()) || (it->second != f));
    }
};

using i_solution = solution<int>;

static const int CHESSMAN_TYPES = 6;
int figures[CHESSMAN_TYPES] = {0};
chessman field[SIZE][SIZE] = {chessman::empty};
int indexes[CHESSMAN_TYPES] = {0};
bool horizontal[SIZE] = {false};
bool vertical[SIZE] = {false};
bool asc_diagonal[2 * SIZE - 1] = {false};
bool desc_diagonal[2 * SIZE - 1] = {false};

int chessman_count() {
    return indexes[CHESSMAN_TYPES - 1];
}

constexpr int chessman_index(chessman f) {
    return static_cast<int>(f) - 1;
}

constexpr chessman chessman_from_index(int i) {
    return static_cast<chessman>(i + 1);
}

void parse(const string &filename) {
    using std::ifstream;
    ifstream in(filename);
    if (!in) {
        throw std::invalid_argument("File does not exist");
    }
    std::regex re("^(?:(\\d+)\\*)?(?:([qQ])|([rR])|([bB])|([nN])|([kK])|([pP]))(?: ([wb]))?$");
    std::smatch m;
    for(string line; std::getline(in, line); ) {
        if (!std::regex_match(line, m, re)) {
            throw std::invalid_argument("Invalid figure");
        }

        int count = 1;
        if (m[1].matched) {
            count = static_cast<int>(std::stoul(string(m[1].first, m[1].second)));
        }

        chessman f;

        if (m[2].matched) {
            f = chessman::queen;
        } else if (m[3].matched) {
            f = chessman::rook;
        } else if (m[4].matched) {
            f = chessman::bishop;
        } else if (m[5].matched) {
            f = chessman::knight;
        } else if (m[6].matched) {
            f = chessman::king;
        } else if (m[7].matched) {
            f = chessman::pawn;
        } else {
            throw std::logic_error("No such figure");
        }

        figures[chessman_index(f)] += count;
    }
}

constexpr int asc_index(int x, int y) {
    return x + y;
}

constexpr int desc_index(int x, int y) {
    return SIZE - 1 + x - y;
}

bool check_chessman(int x, int y, chessman f) {
    if (field[x][y] != chessman::empty
        || horizontal[x]
        || vertical[y]
        || asc_diagonal[asc_index(x, y)]
        || desc_diagonal[desc_index(x, y)]) {
        return false;
    }

    if (f == chessman::queen || f == chessman::rook) {
        for (int i = 0; i < SIZE; ++i) {
            if (field[i][y] != chessman::empty) {
                return false;
            }
        }
        for (int j = 0; j < SIZE; ++j) {
            if (field[x][j] != chessman::empty) {
                return false;
            }
        }
    }

    if (f == chessman::queen || f == chessman::bishop) {
        int top_i, top_j;
        // ascending diagonal
        if (x + y < SIZE) {
            top_i = 0;
            top_j = x + y;
        } else {
            top_i = x + y + 1 - SIZE;
            top_j = SIZE - 1;
        }
        for (int i = top_i, j = top_j; i < SIZE && j >= 0; ++i, --j) {
            if (field[i][j] != chessman::empty) {
                return false;
            }
        }
        // descending diagonal
        if (y >= x) {
            top_i = 0;
            top_j = y - x;
        } else {
            top_i = x - y;
            top_j = 0;
        }
        for (int i = top_i, j = top_j; i < SIZE && j < SIZE; ++i, ++j) {
            if (field[i][j] != chessman::empty) {
                return false;
            }
        }
    }

    if (figures[chessman_index(chessman::king)] > 0) {
        for (int i = std::max(x - 1, 0); i <= std::min(x + 1, SIZE - 1); ++i) {
            for (int j = std::max(y - 1, 0); j <= std::min(y + 1, SIZE - 1); ++j) {
                if (field[i][j] != chessman::empty && (field[i][j] == chessman::king || f == chessman::king)) {
                    return false;
                }
            }
        }
    }

    if (figures[chessman_index(chessman::knight)] > 0) {
        for (int i = -2; i <= 2; ++i) {
            if (i == 0 || x + i < 0) {
                continue;
            } else if (x + i > SIZE - 1) {
                break;
            }

            int j = abs(i) == 2 ? 1 : 2;
            if (y + j < SIZE && field[x + i][y + j] != chessman::empty &&
                (field[x + i][y + j] == chessman::knight || f == chessman::knight)) {
                return false;
            }
            if (y >= j && field[x + i][y - j] != chessman::empty &&
                (field[x + i][y - j] == chessman::knight || f == chessman::knight)) {
                return false;
            }
        }
    }

    if (figures[chessman_index(chessman::pawn)] > 0) {
        if (f == chessman::pawn && x < SIZE - 1) {
            if (y > 0 && field[x + 1][y - 1] != chessman::empty) {
                return false;
            }
            if (y + 1 < SIZE && field[x + 1][y + 1] != chessman::empty) {
                return false;
            }
        }
        if (x > 0) {
            if (y > 0 && field[x - 1][y - 1] == chessman::pawn) {
                return false;
            }
            if (y + 1 < SIZE && field[x - 1][y + 1] == chessman::pawn) {
                return false;
            }
        }
    }

    return true;
}

i_solution get_solution() {
    i_solution s;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (field[i][j] != chessman::empty) {
                s.add_figure(i, j, field[i][j]);
            }
        }
    }
    return s;
}

void set_chessman(int x, int y, chessman f) {
    field[x][y] = f;
    if (f == chessman::queen || f == chessman::rook) {
        horizontal[x] = true;
        vertical[y] = true;
    }

    if (f == chessman::queen || f == chessman::bishop) {
        asc_diagonal[asc_index(x, y)] = true;
        desc_diagonal[desc_index(x, y)] = true;
    }
}

void unset_chessman(int x, int y, chessman f) {
    field[x][y] = chessman::empty;
    if (f == chessman::queen || f == chessman::rook) {
        horizontal[x] = false;
        vertical[y] = false;
    }

    if (f == chessman::queen || f == chessman::bishop) {
        asc_diagonal[asc_index(x, y)] = false;
        desc_diagonal[desc_index(x, y)] = false;
    }
}

void print_debug() {
    cout << "*****START*****\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << chessman_out(field[i][j]) << " ";
        }
        cout << "\n";
    }
    cout << "**\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << horizontal[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << vertical[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < 2 * SIZE - 1; ++i) {
        cout << asc_diagonal[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < 2 * SIZE - 1; ++i) {
        cout << desc_diagonal[i] << " ";
    }
    cout << "\n";
    cout << "*****END*****" << std::endl;
}

unsigned long long int recursive_count = 0;

void recursive_solve(std::vector<i_solution> *solutions, int f_number) {
    ++recursive_count;
    // TODO сделать условием "f_number == chessman_count() - 1" и не делать одну рекурсию лишнюю
    if (f_number == chessman_count()) {
        solutions->push_back(get_solution());
        return;
    }

//    print_debug();

    // TODO передавать предыдущую фигуру и её вертикальную координату. Если фигуры совпадают, то новую ставим не выше предыдущей

    // TODO передавать index ??
    int chessman_index = 0;
    while (indexes[chessman_index] <= f_number) {
        ++chessman_index;
    }
    chessman f = chessman_from_index(chessman_index);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (check_chessman(i, j, f)) {
                set_chessman(i, j, f);
                recursive_solve(solutions, f_number + 1);
                unset_chessman(i, j, f);
            }
        }
    }
}

std::vector<i_solution> solve() {
    int sum = 0;
    for (int i = 0; i < CHESSMAN_TYPES; ++i) {
        sum += figures[i];
        indexes[i] = sum;
    }

    std::vector<i_solution> solutions;
    if (sum != 0) {
        recursive_solve(&solutions, 0);
    }
    cout << "SOLUTIONS SIZE BEFORE = " << solutions.size() << "\n";
    solutions = i_solution::remove_duplicates(&solutions);
    cout << "SOLUTIONS SIZE AFTER = " << solutions.size() << "\n";
    cout << "RECURSIVE CALLS = " << recursive_count << "\n";
    return solutions;
}

int main() {


    parse("../src/input");
    std::vector<i_solution> solutions = solve();
    for (const auto &s : solutions) {
        cout << s << "\n";
    }



    return 0;
}