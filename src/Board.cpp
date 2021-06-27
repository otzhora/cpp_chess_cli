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
        os << (board.turn() ? "White " : "Black ") << "to move" << std::endl;
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

    Board::Board(std::string fen) {
        auto positionLen = fen.find(' ');
        auto position = fen.substr(0, positionLen);
        turn_ = fen[positionLen + 1] == 'w';

        fen.erase(0, positionLen + 3);

        auto castlingLen = fen.find(' ');
        auto castling = fen.substr(0, castlingLen);

        fen.erase(0, castlingLen + 1);

        auto enPassantLen = fen.find(' ');
        auto enPassant = fen.substr(0, enPassantLen);

        fen.erase(0, enPassantLen + 1);

        auto pawnMoveLen = fen.find(' ');
        moves50Rule_ = std::stoi(fen.substr(0, pawnMoveLen));

        fen.erase(0, pawnMoveLen + 1);

        moveCount_ = std::stoi(fen.substr(0));

        // Position
        int row = 0;
        int col = 0;
        for (auto c : position) {
            if (c == '/') {
                row++;
                col = 0;
            } else if (!std::isdigit(c)){
                board_.emplace_back(row, col, new Piece(c));
                col++;
            } else {
                for (int i = 0; i < c - '0'; i++)
                {
                    board_.emplace_back(row, col);
                    col++;
                }
            }
        }

        // Castling
        for (auto c : castling) {
            switch (c) {
                case 'K':
                    castling_.push_back(CastlingRights::WhiteShort);
                    break;
                case 'Q':
                    castling_.push_back(CastlingRights::WhiteLong);
                    break;
                case 'k':
                    castling_.push_back(CastlingRights::BlackShort);
                    break;
                case 'q':
                    castling_.push_back(CastlingRights::BlackLong);
                    break;
                default:
                    castling_.resize(0);
                    break;
            }
        }

        // EnPassant
        if (enPassant != "-") {
            enPassant_ = new Coordinate(enPassant);
        }
    }

    void Board::put_piece(Coordinate coordinate, Piece *piece) {
            int linearCoordinate = coordinate.getLinearCoordinate();
            board_[linearCoordinate] = Field(linearCoordinate, piece);
    }

    void Board::put_piece(int row, int col, Piece *piece) {
        board_[row * BOARD_DIM + col] = Field(row, col, piece);
    }

    Coordinate::Coordinate(int row, char col) {
        row_ = row;
        col_ = std::string("ABCDEFGH").find(col);
        if (col_ == std::string::npos)
            throw std::invalid_argument("You passed invalid coordinate");
    }

    Coordinate::Coordinate(std::string coordinate) {
        if (coordinate.length() != 2)
            throw std::invalid_argument("You passed invalid coordinate");

        int col = std::string("ABCDEFGH").find(::toupper(coordinate[0]));
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

