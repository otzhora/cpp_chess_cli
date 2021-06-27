#include <iostream>

#include "src/Board.h"

using namespace cabbage;

int main() {
    auto board = Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

    std::cout << board;
    return 0;
}
