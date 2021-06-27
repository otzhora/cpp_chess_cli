//
// Created by Yuriy Rogachev on 27.06.2021.
//

#include <iomanip>
#include <iostream>
#include "Piece.h"


namespace cabbage {
    Piece::Piece(Color color, PieceType type) {
        color_ = color;
        type_ = type;
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        char symbol;
        switch (piece.type()) {
            case PieceType::Pawn:
                symbol = piece.color() == Color::Black ? 'p' : 'P';
                break;
            case PieceType::Bishop:
                symbol = piece.color() == Color::Black ? 'b' : 'B';
                break;
            case PieceType::Knight:
                symbol = piece.color() == Color::Black ? 'n' : 'N';
                break;
            case PieceType::Rook:
                symbol = piece.color() == Color::Black ? 'r' : 'R';
                break;
            case PieceType::Queen:
                symbol = piece.color() == Color::Black ? 'q' : 'Q';
                break;
            case PieceType::King:
                symbol = piece.color() == Color::Black ? 'k' : 'K';
                break;
        }

        os << std::setw(2) << symbol;
        return os;
    }

    Piece::Piece(char piece) {
        color_ = isupper(piece) ? Color::White : Color::Black;

        switch(::tolower(piece)) {
            case 'p':
                type_ = PieceType::Pawn;
                break;
            case 'n':
                type_ = PieceType::Knight;
                break;
            case 'b':
                type_ = PieceType::Bishop;
                break;
            case 'r':
                type_ = PieceType::Rook;
                break;
            case 'q':
                type_ = PieceType::Queen;
                break;
            case 'k':
                type_ = PieceType::King;
                break;
        }
    }
}
