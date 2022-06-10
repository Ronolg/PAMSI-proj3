#include "../inc/Board.h"

void Board::print()
{
    std::cout << "   ";
    
    
    for(int i = 0; i<board_size ; i++)
        std::cout << "  " << i << " ";
    std::cout << std::endl;

    
    for(int i = 0; i<board_size ; i++)
    {
        std::cout << " " << i << " | ";
        
        for(int j = 0; j<board_size ;j++)
        {
            if(i%2==0)
            {
                if(j%2==0)
                    std::cout << " " << " | ";
                else 
                {
                    if(_board[i][j].getAlive())
                    {
                        if(_board[i][j].getColor())
                        {
                            if(!_board[i][j].getQueen())    
                                std::cout << "w" << " | ";
                            else
                                std::cout << "W" << " | ";
                        }
                        else 
                        {
                            if(!_board[i][j].getQueen())    
                                std::cout << "b" << " | ";
                            else
                                std::cout << "B" << " | ";
                        }

                    }
                    else
                        std::cout << "." << " | ";
                }    
            }
            else
            {
                if(j%2!=0)
                    std::cout << " " << " | ";
                else 
                {
                    if(_board[i][j].getAlive())
                    {
                        if(_board[i][j].getColor())
                        {
                            if(!_board[i][j].getQueen())    
                                std::cout << "w" << " | ";
                            else
                                std::cout << "W" << " | ";
                        }
                        else 
                        {
                            if(!_board[i][j].getQueen())    
                                std::cout << "b" << " | ";
                            else
                                std::cout << "B" << " | ";
                        }

                    }
                    else
                        std::cout << "." << " | ";
                }  

            }
        }
        std::cout << std::endl;
    }

} 

std::vector<MovePosition> Board::calc_all_moves(short int piece_posX, short int piece_posY)
{
    std::vector<MovePosition> all_moves;
    MovePosition move_pos;
    short int x_m = 1; 
    short int y_m = 1;
    
    const unsigned short int directions = 4;
    bool capture_found[directions];

    for(int i=0; i<directions; i++)
        capture_found[i] = false;

    do
    {
        if(this->_board[piece_posX][piece_posY].getColor() || this->_board[piece_posX][piece_posY].getQueen()) // white or queen move
        {
            if(piece_posX-x_m>=0 && piece_posY-y_m>=0 && !capture_found[0])
            {
                if(!this->_board[piece_posX-x_m][piece_posY-y_m].getAlive())
                {
                    move_pos._x = piece_posX - x_m; 
                    move_pos._y = piece_posY - y_m;
                    all_moves.push_back(move_pos);
                }
                else
                {
                    if(this->_board[piece_posX][piece_posY].getColor()!=this->_board[piece_posX-x_m][piece_posY-y_m].getColor())
                    {
                        capture_found[0] = true;
                        this->calc_captures(all_moves, piece_posX, piece_posY, piece_posX-x_m, piece_posY-y_m); // bottom left capture
                    }
                }   
            }

            if(piece_posX-x_m>=0 && piece_posY+y_m<board_size && !capture_found[1])
            {
                if(!this->_board[piece_posX-x_m][piece_posY+y_m].getAlive())
                {
                    move_pos._x = piece_posX - x_m; 
                    move_pos._y = piece_posY + y_m;
                    all_moves.push_back(move_pos);
                }  
                else
                {
                    if(this->_board[piece_posX][piece_posY].getColor()!=this->_board[piece_posX-x_m][piece_posY+y_m].getColor())
                    {
                        capture_found[1] = true;
                        this->calc_captures(all_moves, piece_posX, piece_posY, piece_posX-x_m, piece_posY+y_m); // bottom left capture
                    } 
                }  
            }
        }
        
        if(!this->_board[piece_posX][piece_posY].getColor() || this->_board[piece_posX][piece_posY].getQueen()) // black or queen move
        {
            if(piece_posX+x_m<board_size && piece_posY-y_m>=0 && !capture_found[2])
            {
                if(!this->_board[piece_posX+x_m][piece_posY-y_m].getAlive())
                {
                    move_pos._x = piece_posX + x_m; 
                    move_pos._y = piece_posY - y_m;
                    all_moves.push_back(move_pos);
                }
                else
                {
                    if(this->_board[piece_posX][piece_posY].getColor()!=this->_board[piece_posX+x_m][piece_posY-y_m].getColor())
                    {
                        capture_found[2] = true;
                        this->calc_captures(all_moves, piece_posX, piece_posY, piece_posX+x_m, piece_posY-y_m); // bottom left capture
                    }
                }   
            }
            if(piece_posX+x_m<board_size && piece_posY+y_m<board_size && !capture_found[3])
            {
                if(!this->_board[piece_posX+x_m][piece_posY+y_m].getAlive())
                {
                    move_pos._x = piece_posX + x_m; 
                    move_pos._y = piece_posY + y_m;
                    all_moves.push_back(move_pos);
                }  
                else
                {
                    if(this->_board[piece_posX][piece_posY].getColor()!=this->_board[piece_posX+x_m][piece_posY+y_m].getColor())
                    {
                        capture_found[3] = true;
                        this->calc_captures(all_moves, piece_posX, piece_posY, piece_posX+x_m, piece_posY+y_m); // bottom right capture
                    }
                }  
            }
        }
        
        x_m++;
        y_m++;

    }while(this->_board[piece_posX][piece_posY].getQueen() && (piece_posX-x_m>=0 || piece_posX+x_m<board_size || piece_posY-y_m>=0 || piece_posY+y_m<board_size));

    return all_moves;
}

void Board::calc_captures(std::vector<MovePosition>& moves, short int piece_posX, short int piece_posY, short int enemy_posX, short int enemy_posY)
{
    short int x = 1; //
    short int y = 1; // 
    MovePosition capture_move;

    do{
   
        if(piece_posX>enemy_posX && piece_posY>enemy_posY) // top left
        {
            if(enemy_posX-x>=0 && enemy_posY-y>=0)
            {
                if(!this->_board[enemy_posX-x][enemy_posY-y].getAlive())
                {
                    capture_move._x = enemy_posX - x;
                    capture_move._y = enemy_posY - y;
                    capture_move.isCapture = true;
                    moves.push_back(capture_move);

                }
            }
        }

        if(piece_posX>enemy_posX && piece_posY<enemy_posY) // top right
        {
            if(enemy_posX-x>=0 && enemy_posY+y<board_size)
            {
                if(!this->_board[enemy_posX-x][enemy_posY+y].getAlive())
                {
                    capture_move._x = enemy_posX - x;
                    capture_move._y = enemy_posY + y;
                    capture_move.isCapture = true;
                    moves.push_back(capture_move);
                }
            }
        }

        if(piece_posX<enemy_posX && piece_posY>enemy_posY) // bottom left
        {
            
            if(enemy_posX+x<board_size && enemy_posY-y>=0)
            {
                if(!this->_board[enemy_posX+x][enemy_posY-y].getAlive())
                {
                    capture_move._x = enemy_posX + x;
                    capture_move._y = enemy_posY - y;
                    capture_move.isCapture = true;
                    moves.push_back(capture_move);
                }
            }
        }
        
        if(piece_posX<enemy_posX && piece_posY<enemy_posY) // bottom right
        {
            if(enemy_posX+x<board_size && enemy_posY+y<board_size)
            {
                if(!this->_board[enemy_posX+x][enemy_posY+y].getAlive())
                {
                    capture_move._x = enemy_posX + x;
                    capture_move._y = enemy_posY + y;
                    capture_move.isCapture = true;
                    moves.push_back(capture_move);
                }
            }
        }
        
        x++; y++;

    }while(this->_board[piece_posX][piece_posY].getQueen() && (piece_posX-x>=0 || piece_posX+x<board_size || piece_posY-y>=0 || piece_posY+y<board_size));
}

MovePosition Board::find_piece(short int xo, short int yo, short int xk, short int yk)
{
    
    short int xi=1;
    short int yi=1;
    MovePosition found_pos;
    bool isfound = false;

    found_pos._x = -1; //
    found_pos._y = -1; // if nothing was found 

    
    do{
        if(xo>xk && yo>yk) // top left
        {
            if(this->_board[xo-xi][yo-yi].getAlive())
            {
                found_pos._x = xo - xi;
                found_pos._y = yo - yi;
                isfound = true;
            }
        }

        if(xo>xk && yo<yk) // top right
        {
            if(this->_board[xo-xi][yo+yi].getAlive())
            {
                found_pos._x = xo - xi;
                found_pos._y = yo + yi;
                isfound = true;
            }
        }

        if(xo<xk && yo>yk) // bottom left
        {
           if(this->_board[xo+xi][yo-yi].getAlive())
            {
                found_pos._x = xo + xi;
                found_pos._y = yo - yi;
                isfound = true;
            }
        }
        
        if(xo<xk && yo<yk) // bottom right
        {
            if(this->_board[xo+xi][yo+yi].getAlive())
            {
                found_pos._x = xo + xi;
                found_pos._y = yo + yi;
                isfound = true;
            }
        }
        xi++; yi++;

    }while(!isfound && (xo-xi>=0 || xo+xi<board_size || yo-yi>=0 || yo+yi<board_size));

    return found_pos;
}

bool Board::operator==(const Board& b)const
{
    int count = 0;

    for(int i=0; i<board_size; i++)
    {
        for(int j=0; j<board_size; j++)
        {
            if(this->_board[i][j] == b._board[i][j])
               count++;
        }
    }
    
    return (count==board_size*board_size) ? true : false;
}
