//
// Created by Yuriy Rogachev on 26.06.2021.
//

#ifndef CABBAGE_PIECE_H
#define CABBAGE_PIECE_H

namespace cabbage {
    enum Color {
        White,
        Black
    };

    enum PieceType {
        Pawn,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };

    class Piece {
    private:
        PieceType type_;
        Color color_;

    public:
        explicit Piece(char piece);
        explicit Piece(Color color, PieceType type);

        friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

        [[nodiscard]] PieceType type() const { return type_; }
        [[nodiscard]] Color color() const { return color_; }
    };

}

#endif //CABBAGE_PIECE_H
