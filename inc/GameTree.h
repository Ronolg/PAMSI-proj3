#ifndef GAMETREE_H
#define GAMETREE_H

#include "../inc/Board.h"
#include "../inc/Player.h"
#include "../inc/Position.h"

#include <iostream>
#include <vector>
#include <memory>


class GameTree : public std::enable_shared_from_this<GameTree>
{
    public:
    
        int move_value; //describes how good move is, positive (max) values means move is good for human player, negatives (min) -> AIplayer
        Board move_board;
        std::vector<std::shared_ptr<GameTree>> leaves;

        
        GameTree(Board board);

        void add_leaf(Board board);
        void create(Board board, unsigned short int moves, Player white_player, Player black_player); // creates game tree for next moves
        std::shared_ptr<GameTree> search_for(const Board board);

};

#endif