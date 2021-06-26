#include <iostream>

#include "src/Board.h"

using namespace cabbage;

int main() {
    auto board = Board();
    board.put_piece(Coordinate("A1"), Piece::Rook);
    board.put_piece(Coordinate("E4"), Piece::Pawn);
    board.put_piece(Coordinate("E8"), Piece::King);
    board.put_piece(Coordinate("B7"), Piece::Queen);
    board.put_piece(Coordinate("H8"), Piece::Knight);
    board.put_piece(Coordinate("H1"), Piece::King);

    std::cout << board;
    return 0;
}
