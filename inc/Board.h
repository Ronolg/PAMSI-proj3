#ifndef BOARD_H
#define BOARD_H

#include "../inc/Piece.h"
#include "../inc/Position.h"


#include <iostream>
#include <vector>


const static short int board_size = 8;

class Piece;

struct Board
{
        Piece _board[board_size][board_size];

        void print();  
        
        std::vector<MovePosition> calc_all_moves(short int piece_posX, short int piece_posY);
        void calc_captures(std::vector<MovePosition>& moves, short int piece_posX, short int piece_posY, short int enemy_posX, short int enemy_posY);
        MovePosition find_piece(short int xo, short int yo, short int xk, short int yk);

        bool operator==(const Board& b) const;

};

#endif