//
// Created by Yuriy Rogachev on 26.06.2021.
//

#ifndef CABBAGE_BOARD_H
#define CABBAGE_BOARD_H

#define BOARD_DIM 8

#include <vector>
#include <iostream>
#include <string>

#include "Piece.h"


namespace cabbage{
    enum CastlingRights {
        WhiteShort,
        WhiteLong,
        BlackShort,
        BlackLong
    };


    class Field {
    private:
        bool isWhite_;
        Piece* piece_;
    public:
        explicit Field(int coordinate);
        explicit Field(int coordinate, Piece* piece);
        explicit Field(int row, int col);
        explicit Field(int row, int col, Piece* piece);
        explicit Field(Field *pField);

        Field& operator=(Field *pField);
        friend std::ostream& operator<<(std::ostream& os, const Field& board);

        [[nodiscard]] Piece* piece() const { return piece_; }
        void piece(Piece* p) { piece_ = p; }
        [[nodiscard]] bool isWhite() const { return isWhite_; }
    };

    class Coordinate {
    private:
        int row_;
        int col_;
    public:
        explicit Coordinate(std::string coordinate);
        Coordinate(int row, char col);

        [[nodiscard]] int getLinearCoordinate() const;
    };


    class Board {
    private:
        bool turn_;
        std::vector<Field> board_;
        std::vector<CastlingRights> castling_;
        int moveCount_;
        Coordinate *enPassant_;
        int moves50Rule_;

    public:
        explicit Board(std::string fen);

        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        [[nodiscard]] bool turn() const { return turn_; }
        [[nodiscard]] std::vector<CastlingRights> castling() const { return castling_; }
        [[nodiscard]] int moveCount() const { return moveCount_; }
        [[nodiscard]] Coordinate* enPassant() const { return enPassant_; }
        [[nodiscard]] int moves50Rule() const { return moves50Rule_; }

        void put_piece(Coordinate coordinate, Piece* piece);
        void put_piece(int row, int col, Piece* piece);
    };


    bool getSquareColor(int row, int col);
}

#endif //CABBAGE_BOARD_H
