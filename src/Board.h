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
    class Field {
    private:
        bool isWhite_;
        Piece piece_;
    public:
        explicit Field(int coordinate);
        explicit Field(int coordinate, Piece piece);
        explicit Field(int row, int col);
        explicit Field(int row, int col, Piece piece);
        explicit Field(Field *pField);

        Field& operator=(Field *pField);
        friend std::ostream& operator<<(std::ostream& os, const Field& board);

        [[nodiscard]] Piece piece() const { return piece_; }
        void piece(Piece p) { piece_ = p; }
        [[nodiscard]] bool isWhite() const { return isWhite_; }
    };

    class Coordinate {
    private:
        int row_;
        char col_;
    public:
        explicit Coordinate(std::string coordinate);
        Coordinate(int row, char col);

        int getLinearCoordinate();
    };


    class Board {
    private:
        std::vector<Field> board_;
    public:
        Board();

        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        void put_piece(Coordinate coordinate, Piece piece) {
            int linearCoordinate = coordinate.getLinearCoordinate();
            board_[linearCoordinate] = Field(linearCoordinate, piece);
        }
    };


    bool getSquareColor(int row, int col);
}

#endif //CABBAGE_BOARD_H
