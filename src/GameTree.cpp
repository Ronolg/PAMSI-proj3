#include "../inc/GameTree.h"

GameTree::GameTree(Board board)
{
    move_board = board;
    move_value = 0;
}

void GameTree::add_leaf(Board board)
{
    std::shared_ptr<GameTree> leaf = std::make_shared<GameTree>(board);

    this->leaves.push_back(leaf);
}


void GameTree::create(Board board, unsigned short int moves, Player white_player, Player black_player)
{
    short int current_move = 1;
    bool white = true;
    bool black = false;
    std::vector<MovePosition> possible_moves;
    Board copy_board;
    MovePosition captured_pos;

    std::shared_ptr<GameTree> root = shared_from_this();
    std::shared_ptr<GameTree> tmp;


    while(current_move <= moves)
    {
        for(int i=0; i<board_size; i++)
        {
            for(int j=0; j<board_size; j++)
            {
                if(current_move%2==1)
                {
                    if(white_player.check_selected_piece(board, i, j, white))
                    {
                        possible_moves = board.calc_all_moves(i, j);
                        for(auto elem : possible_moves)
                        {
                            copy_board = board;
                            if(elem.isCapture)
                            {
                                tmp->move_value+=2;
                                captured_pos = copy_board.find_piece(i,j,elem._x, elem._y);
                                if(captured_pos._x>-1)
                                {
                                    copy_board._board[captured_pos._x][captured_pos._y].setAlive(false); // capturing black piece
                                } 
                            }
                            swap(copy_board._board[i][j], copy_board._board[elem._x][elem._y]);
                            root->add_leaf(copy_board);
                        }
                    }

                }
                else
                {
                    if(black_player.check_selected_piece(board, i, j, black))
                    {
                        for(unsigned int k = 0; k<root->leaves.size(); k++)
                        { 
                            tmp = root->leaves[k];
                            possible_moves = tmp->move_board.calc_all_moves(i, j);
                            for(auto elem : possible_moves)
                            {
                                copy_board = tmp->move_board;
                                if(elem.isCapture)
                                {
                                    tmp->move_value-=2;
                                    captured_pos = copy_board.find_piece(i,j,elem._x, elem._y);
                                    if(captured_pos._x>-1)
                                    {
                                        copy_board._board[captured_pos._x][captured_pos._y].setAlive(false); // capturing white piece
                                    } 
                                } 

                                swap(copy_board._board[i][j], copy_board._board[elem._x][elem._y]);
                                tmp->add_leaf(copy_board);
                            }
                        
                        }
                    }
                }
            }
        }
        current_move++;
    }

}


std::shared_ptr<GameTree> GameTree::search_for(const Board board)
{
    std::shared_ptr<GameTree> found;

    if(this->move_board == board)
    {
        found = shared_from_this();
        return found;
    }
    if(!this->leaves.empty())
    {
        for(unsigned int i = 0; i<this->leaves.size(); i++)
        {
            found = this->leaves[i]->search_for(board);
            if(found != nullptr)
                return found;
        }
    }

    return nullptr;
}