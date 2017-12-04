#include <iostream>

#include <string>
#include <list>
#include <regex>
#include <exception>
#include <vector>
#include <list>

namespace chessy {

using std::cout;
using std::string;
static const int SIZE = 3;

unsigned long long int iterations = 0;

chessman field[SIZE][SIZE] = {chessman::empty};
int indexes[CHESSMAN_TYPES] = {0};

int chessman_count() {
    return indexes[CHESSMAN_TYPES - 1];
}


}