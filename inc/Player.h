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
        unsigned short int _player_pieces; //tracks number of player pieces
    
    public:
        Player();
        Player(Board& board, bool color);

        unsigned short int getPlayerPieces()const {return this->_player_pieces;};
        void setPlayerPieces(unsigned short int a){this->_player_pieces = a;};
        
        /* Checks if player chose correct piece
            Parameters:
            board - current state of the game board
            x, y - selection cords
            color - color of selected piece
            return value: true if selection was correct, false if selection was incorrect
         */
        bool check_selected_piece(Board& board, short int x, short int y, bool color) const; 
        
        /* Checks if player chose correct move position
            Parameters:
            board - current state of the game board
            piece_posX, piece_posY - cords of moving piece
            desired x, desired y - cords of position the piece is supposed to move to
            return value: true if selection was correct, false if selection was incorrect
         */
        bool check_selected_pos(Board& board, short int piece_posX, short int piece_posY, short int desiredX, short int desiredY) const;   // checks if player chose correct position to move to
        
        /* Checks if player chose correct move position
            Parameters:
            board - current state of the game board
            x, y - chain capture starting position
            color - color of capturing piece
            return value: true if chain capture occurs, false if chain capture does not occur
         */
        bool check_chain_capture(Board& board, short int x, short int y, bool color) const;  // checks if chain capture is available
        
        /* Menages scenario when queen attempts to capture more than 1 piece with one move.
            Parameters:
            board - current state of the game board
            starting_x, starting_y - starting position
            desired_x, desired_y - cords of position the piece is supposed to move to
            return value: true if queen capture is correct, false if queen capture is incorrect
         */
        bool check_multi_capture(Board& board, short int starting_x, short int starting_y, short int desired_x, short int desired_y, unsigned short int direction) const; 

        /* Realizes capture
            Parameters:
            board - current state of the game board
            enemyPlayer - enemy player
            starting_x, starting_y - starting position
            desired_x, desired_y - cords of position the piece is supposed to move to
            return value: true if capture is correct, false if capture is incorrect
         */
        bool capture(Board& board, Player& enemyPlayer, short int starting_x, short int starting_y, short int desired_x, short int desired_y) const;

};


#endif