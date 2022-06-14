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

        void print(); // prints board
        /* Counts pieces on board for specific player
           Parameters:
           color - determines pieces of what color are count
           return: returns number of pieces 
         */
        unsigned short int count_pieces(bool color);

        /* Calculates all possible moves for specific piece
           Parameters:
           piece_posX, piece_posY - position of piece
           return: returns all possible moves inside std::vector
         */
        std::vector<MovePosition> calc_all_moves(short int piece_posX, short int piece_posY);

         /* Calculates all possible capture moves for specific piece
           Parameters:
           moves - container for all possible captures (chain captures inc.) 
           piece_posX, piece_posY - position of piece
           enemy_piece - position of enemy piece
           color - color of piece which captures
         */
        void calc_captures(std::vector<MovePosition>& moves, short int piece_posX, short int piece_posY, MovePosition& enemy_piece, const bool color);
        
        /* Check if made move leads to lost piece (leads to capture) 
           Parameters:
           piece_posX, piece_posY - position of piece
           return value: true if move led to being captured by enemy, false if move did not lead to being captured by enemy
         */
        bool isLost(short int piece_posX, short int piece_posY);

        /*  Finds piece between (xo,yo) and (xk, yk) 
           Parameters:
           xo,yo - starting positon
           xk,yk - final positon
           return value: position of found piece. If nothing was found func returns position (-1, -1)

         */
        MovePosition find_piece(short int xo, short int yo, short int xk, short int yk);

        bool operator==(const Board& b) const;

};

#endif