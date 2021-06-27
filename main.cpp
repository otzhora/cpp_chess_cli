#include <iostream>

#include "src/Board.h"

using namespace cabbage;

int main() {
    auto board = Board();
    board.put_piece(Coordinate("A1"), new Piece(Color::White, PieceType::Rook));
    board.put_piece(Coordinate("E4"), new Piece(Color::Black, PieceType::Rook));
    board.put_piece(Coordinate("E8"), new Piece(Color::White, PieceType::Pawn));
    board.put_piece(Coordinate("B7"), new Piece(Color::Black, PieceType::Pawn));
    board.put_piece(Coordinate("H8"), new Piece(Color::White, PieceType::Knight));
    board.put_piece(Coordinate("H1"), new Piece(Color::Black, PieceType::Knight));
    board.put_piece(Coordinate("F8"), new Piece(Color::White, PieceType::Bishop));
    board.put_piece(Coordinate("F2"), new Piece(Color::Black, PieceType::Bishop));
    board.put_piece(Coordinate("G3"), new Piece(Color::White, PieceType::Queen));
    board.put_piece(Coordinate("C1"), new Piece(Color::Black, PieceType::Queen));
    board.put_piece(Coordinate("D3"), new Piece(Color::White, PieceType::King));
    board.put_piece(Coordinate("F3"), new Piece(Color::Black, PieceType::King));

    std::cout << board;
    return 0;
}
