#ifndef PLAYER_H
#define PLAYER_H

#include "../inc/Piece.h"
#include "../inc/Board.h"

#include <iostream>

const static short int max_pieces = 12;
const static short int all_directions = 4;

class Piece;

class Player
{
    protected:
        unsigned short int _player_pieces;
    
    public:
        Player();
        Player(Board& board, bool color);

        unsigned short int getPlayerPieces()const {return this->_player_pieces;};
        void setPlayerPieces(unsigned short int a){this->_player_pieces = a;};
        
        bool check_selected_piece(Board& board, short int x, short int y, bool color) const; // checks if player chose correct piece
        bool check_selected_pos(Board& board, short int piece_posX, short int piece_posY, short int desiredX, short int desiredY) const;   // checks if player chose correct position to move to
        bool check_chain_capture(Board& board, short int x, short int y, bool color) const;  // checks if chain capture is available
        bool check_multi_capture(Board& board, short int starting_x, short int starting_y, short int desired_x, short int desired_y, unsigned short int direction) const; // menages scenario when queen attempts to capture more than 1 piece with one move.

        bool capture(Board& board, Player& enemyPlayer, short int starting_x, short int starting_y, short int desired_x, short int desired_y) const;
        //void move(Piece& piece, short int desired_x, short int desired_y);

};


#endif