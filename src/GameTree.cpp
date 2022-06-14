#include "../inc/GameTree.h"

GameTree::GameTree(Board board)
{
    move_board = board;
    move_value = 0;
}

void GameTree::add_leaf(Board board, short int mv_value)
{
    std::shared_ptr<GameTree> leaf = std::make_shared<GameTree>(board);
    leaf->move_value  = this->move_value + mv_value;
    this->leaves.push_back(leaf);
}


void GameTree::create(Board board, unsigned short int moves, Player white_player, Player black_player)
{
    short int current_move = 1;
   
    while(current_move<=moves)
    {
        this->fill(board, current_move, white_player, black_player);
        current_move++;
    };
 
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

void GameTree::fill(Board& board, short int moves, Player white_player, Player black_player)
{
    std::vector<MovePosition> possible_moves;
    Board copy_board; // copy of current state of the board
    MovePosition captured_pos; // position of captured enemy
    bool white = true;
    bool black = false;
    short int move_quality; // determines how good move was. The lowest -> best black player move, the highest -> best white player move

    this->move_board = board;

    if(this->leaves.empty())
    {
        for(int i=0; i<board_size; i++) //for each game piece calculate poss moves
        {
            for(int j=0; j<board_size; j++)
            {
                if(moves%2 == 1) //whites turn
                {
                    if(white_player.check_selected_piece(board, i, j, white))// check if piece selection was correct
                    {
                        possible_moves = this->move_board.calc_all_moves(i, j); // calculates all possible moves
                        for(auto elem : possible_moves)
                        {
                            move_quality = 0; // by default moves have values of 0
                            copy_board = this->move_board; // create a copy of current state of the game board
                            
                            if(elem.isCapture) 
                            {
                                move_quality = move_quality + elem.capture_count*2; // each capture count as +-2
                                
                                for(auto elem2 : elem.captured_enemies)
                                    copy_board._board[elem2._x][elem2._y].setAlive(false); // capturing black piece
                              
                            }
                            
                            if(elem._x==0 && !copy_board._board[elem._x][elem._y].getQueen()) // creating white queen
                            {   
                                copy_board._board[i][j].setQueen(true);           
                                move_quality = move_quality + 5; // creating a Quenn yields 5 points
     
                            
                            }

                            swap(copy_board._board[i][j], copy_board._board[elem._x][elem._y]); // make the move
                            
                            if(copy_board.isLost(elem._x, elem._y)) //additial move criteria that checks if made move leads to lost piece
                                move_quality = move_quality - 1;
                            
                            this->add_leaf(copy_board, move_quality);

                        }
                    }
                }
                else // blacks turn
                {
                    if(black_player.check_selected_piece(board, i, j, black))// check if piece selection was correct
                    {
                        possible_moves = this->move_board.calc_all_moves(i, j);// calculates all possible moves
                        for(auto elem : possible_moves)
                        {
                            move_quality = 0;// by default moves have values of 0
                            copy_board = this->move_board;// create a copy of current state of the game board
                            
                            if(elem.isCapture)
                            {
                                move_quality = move_quality - elem.capture_count*2;// each capture count as +-2
                                
                                for(auto elem2 : elem.captured_enemies)
                                    copy_board._board[elem2._x][elem2._y].setAlive(false); // capturing black piece

                            }

                            if(elem._x==board_size-1 && !copy_board._board[elem._x][elem._y].getQueen()) //creating black queen
                            {    
                                copy_board._board[i][j].setQueen(true);
                                move_quality = move_quality - 5;// creating a Quenn yields 5 points

                            }

                            swap(copy_board._board[i][j], copy_board._board[elem._x][elem._y]);

                            if(copy_board.isLost(elem._x, elem._y))
                                move_quality = move_quality + 1;//additial move criteria that checks if made move leads to lost piece
                            
                            this->add_leaf(copy_board, move_quality);
                        }
                    }
                }
            }
        }
        
    }
    else
    {
        for(unsigned int i = 0; i<this->leaves.size(); i++)
            this->leaves[i]->fill(this->leaves[i]->move_board, moves, white_player, black_player);
    }

}

void GameTree::find_best_move(int& min, std::vector<std::shared_ptr<GameTree>>& path, std::vector<std::shared_ptr<GameTree>>& tmp)
{
    std::shared_ptr<GameTree> parent;

    parent = shared_from_this();
    tmp.push_back(parent);

    if(!this->leaves.empty())
    {
        for(unsigned int i = 0; i<this->leaves.size(); i++)   
            this->leaves[i]->find_best_move(min, path, tmp);
    }
    else
    {
        if(this->move_value < min)
        {
            min = this->move_value;
            if(path.size() > tmp.size())
            {
                path.erase(path.end()-tmp.size(), path.end());
                for(unsigned int i = 0; i<tmp.size();i++)      
                    path.push_back(tmp[i]);  
                
                tmp.clear();
            }
            else
            {
                path = tmp;
                //tmp.back() = nullptr;
                tmp.pop_back();
            }   
        }
        else
            tmp.pop_back();
    }

}

void GameTree::print()
{
    if(this->leaves.empty())
    {
        this->move_board.print();
        std::cout << std::endl;
        std::cout << this->move_value << std::endl;
        std::cout << std::endl;
    }
    else
    {
        for(unsigned int i = 0; i<this->leaves.size(); i++)
            this->leaves[i]->print();
    }
    
}