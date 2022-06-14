#ifndef GAMETREE_H
#define GAMETREE_H

#include "../inc/Board.h"
#include "../inc/Player.h"
#include "../inc/Position.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>



class GameTree : public std::enable_shared_from_this<GameTree>
{
    public:
    
        int move_value; //describes how good move is, positive (max) values means move is good for human player, negatives (min) -> AIplayer
        Board move_board;   // stored move
        std::vector<std::shared_ptr<GameTree>> leaves;

        
        /* 
            Initializes Game Tree with parameter: board and sets it move_value to 0 
         */
        GameTree(Board board);

        /* Adds leaf to the Game Tree.
            Parameters:
            board - board to which move_board attribute is set to
            mv_value - value to which move_value attribute is set to
         */
        void add_leaf(Board board, short int mv_value);
        
        /* Creates game tree for next moves
            Parameters:
            board - starting board which will be stored in root
            moves - determines for how many moves Game Tree will be created
            white_player
            black_player
         */
        void create(Board board, unsigned short int moves, Player white_player, Player black_player); 
        
        /*  Searches Game Tree for specific element 
            Parameters:
            board - searched element
            return value: returns pointer to searched element assuming it was found. If element was not found func returns nullptr
         */
        std::shared_ptr<GameTree> search_for(const Board board);

        /* Fills tree with specific number of possible moves for current state of game board 
            Parameters: 
            board - parameter which determines current state of the game board
            moves - tracks number of moves (helps to decide which player is making a move -> if moves is odd number it means white moves etc.)
            white_player
            black_player
         */
        void fill(Board& board, short int moves, Player white_player, Player black_player);
        
        /* Finds the best possible move (with the lowest move_value)
            Parameters: 
            min - minimal value of tree
            path - smart pointers to each node in branch with minimal value
            tmp - auxiliary parameter that helps with creation of path to minimal element

         */
        void find_best_move(int& min, std::vector<std::shared_ptr<GameTree>>& path, std::vector<std::shared_ptr<GameTree>>& tmp);
        
        
        void print(); // prints game tree
};

#endif