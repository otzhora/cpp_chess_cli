//
// Created by Yuriy Rogachev on 26.06.2021.
//

#include <iomanip>

#include "Board.h"

namespace cabbage {
    bool getSquareColor(int row, int col) {
        if (row % 2 == 0) {
            return !(col % 2);
        }
        else {
            return col % 2;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Field &field) {
        char symbol;

        if (field.piece() == nullptr) {
            symbol = field.isWhite() ? '.' : '*';
            os << std::setw(2) << symbol;
        } else {
            os << std::setw(2) << *field.piece();
        }
        return os;
    }

    Field::Field(int row, int col) {
        isWhite_ = getSquareColor(row, col);
        piece_ = nullptr;
    }

    Field::Field(Field *pField) {
        isWhite_ = pField->isWhite();
        piece_ = pField->piece();
    }

    Field &Field::operator=(Field *pField) {
        isWhite_ = pField->isWhite();
        piece_ = pField->piece();
        return *this;
    }

    Field::Field(int row, int col, Piece *piece) {
        isWhite_ = getSquareColor(row, col);
        piece_ = piece;
    }

    Field::Field(int coordinate) {
        int row = coordinate / BOARD_DIM;
        int col = coordinate - row * BOARD_DIM;

        isWhite_ = getSquareColor(row, col);
        piece_ = nullptr;
    }

    Field::Field(int coordinate, Piece* piece) {
        int row = coordinate / BOARD_DIM;
        int col = coordinate - row * BOARD_DIM;

        isWhite_ = getSquareColor(row, col);
        piece_ = piece;
    }

    std::ostream &operator<<(std::ostream &os, const Board &board) {
        for (int row = 0; row < BOARD_DIM; row++) {
            os << std::setw(2) << BOARD_DIM - row;
            for (int col = 0; col < BOARD_DIM; col++){
                os << std::setw(2) << board.board_[row * BOARD_DIM + col];
            }
            os << std::endl;
        }
        os << std::setw(2) << " ";
        for (int i = 0; i < BOARD_DIM; i++) {
            os << std::setw(2) << "ABCDEFGH"[i];
        }
        return os;
    }

    Board::Board() {
        for (int row = 0; row < BOARD_DIM; row++) {
            for (int col = 0; col < BOARD_DIM; col++) {
                board_.emplace_back(row, col);
            }
        }
    }

    Coordinate::Coordinate(int row, char col) {
        row_ = row;
        col_ = col;
    }

    Coordinate::Coordinate(std::string coordinate) {
        if (coordinate.length() != 2)
            throw std::invalid_argument("You passed invalid coordinate");

        int col = std::string("ABCDEFGH").find(coordinate[0]);
        if (col == std::string::npos)
            throw std::invalid_argument("You passed invalid coordinate");

        int row = BOARD_DIM - int(coordinate[1]) + '0';
        if (row < 0 || row >= BOARD_DIM)
            throw std::invalid_argument("You passed invalid coordinate");

        row_ = row;
        col_ = col;
    }

    int Coordinate::getLinearCoordinate() const {
        return row_ * BOARD_DIM + col_;
    }
}

