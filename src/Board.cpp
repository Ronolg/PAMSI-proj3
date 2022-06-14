#include "../inc/Board.h"


unsigned short int Board::count_pieces(bool color)
{
    unsigned short int piece_count = 0;
    for(int i=0; i<board_size; i++)
    {
        for(int j=0; j<board_size; j++)
        {
            if(this->_board[i][j].getColor() == color)
                piece_count++;
        }
    }
    return piece_count;
}

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
    MovePosition enemy_piece;
    MovePosition move_pos;
    short int x_m = 1; // auxiliary variables used for iterating through game board
    short int y_m = 1; //
    
    const unsigned short int directions = 4; // number of all possible directions: top left, top right, bottom left, bottom right
    bool capture_found[directions];

    for(int i=0; i<directions; i++)
        capture_found[i] = false;

    do
    {   //top left ===================================
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
                        enemy_piece._x = piece_posX - x_m;
                        enemy_piece._y = piece_posY - y_m;
                        
                        this->calc_captures(all_moves, piece_posX, piece_posY, enemy_piece, this->_board[piece_posX][piece_posY].getColor()); // top left capture
                    }
                }   
            }

        // top right ===================================
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
                        enemy_piece._x = piece_posX - x_m;
                        enemy_piece._y = piece_posY + y_m;
                        this->calc_captures(all_moves, piece_posX, piece_posY, enemy_piece, this->_board[piece_posX][piece_posY].getColor()); // top right capture
                    } 
                }  
            }
        }
        // bottom left ===================================
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
                        enemy_piece._x = piece_posX + x_m;
                        enemy_piece._y = piece_posY - y_m;
                        this->calc_captures(all_moves, piece_posX, piece_posY, enemy_piece, this->_board[piece_posX][piece_posY].getColor()); // bottom left capture
                    }
                }   
            }
            // bottom right ===================================
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
                        enemy_piece._x = piece_posX + x_m;
                        enemy_piece._y = piece_posY + y_m;
                        this->calc_captures(all_moves, piece_posX, piece_posY, enemy_piece, this->_board[piece_posX][piece_posY].getColor()); // bottom right capture
                    }
                }  
            }
        }
        
        x_m++;
        y_m++;

    }while(this->_board[piece_posX][piece_posY].getQueen() && (piece_posX-x_m>=0 || piece_posX+x_m<board_size || piece_posY-y_m>=0 || piece_posY+y_m<board_size));

    return all_moves;
}

void Board::calc_captures(std::vector<MovePosition>& moves, short int piece_posX, short int piece_posY, MovePosition& enemy_piece, const bool color)
{
    short int x = 1; //
    short int y = 1; //  cords used to iterate through current board

    short int x_chain; //
    short int y_chain; // cords used to iterate through board when chain capture occurs

    MovePosition enemy_piece_cp = enemy_piece;
    MovePosition chain_capture;

    do{
   
        if(piece_posX>enemy_piece_cp._x && piece_posY>enemy_piece_cp._y) // top left
        {
            if(enemy_piece_cp._x-x>=0 && enemy_piece_cp._y-y>=0)
            {
                if(!this->_board[enemy_piece_cp._x-x][enemy_piece_cp._y-y].getAlive())
                {
                    enemy_piece._x = enemy_piece_cp._x - x;
                    enemy_piece._y = enemy_piece_cp._y - y;
                    enemy_piece.isCapture = true;
                    enemy_piece.capture_count = enemy_piece.capture_count + 1;   
                    enemy_piece.captured_enemies.push_back(enemy_piece_cp);                

                   
                    x_chain = 1;
                    y_chain = 1;

                    do{
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x-x_chain][enemy_piece._y-y_chain].getAlive() && this->_board[enemy_piece._x-x_chain][enemy_piece._y-y_chain].getColor() != color) // top left chain capture
                        {    
                            chain_capture._x = chain_capture._x - x_chain;
                            chain_capture._y = chain_capture._y - y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x-x_chain][enemy_piece._y+y_chain].getAlive() && this->_board[enemy_piece._x-x_chain][enemy_piece._y+y_chain].getColor() != color) // top right chain capture
                        {    
                            chain_capture._x = chain_capture._x - x_chain;
                            chain_capture._y = chain_capture._y + y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x+x_chain][enemy_piece._y-y_chain].getAlive() && this->_board[enemy_piece._x+x_chain][enemy_piece._y-y_chain].getColor() != color) // bottom left chain capture
                        {    
                            chain_capture._x = chain_capture._x + x_chain;
                            chain_capture._y = chain_capture._y - y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        //bottom right chain capture is not possible as capture was made from this direction

                        x_chain++;
                        y_chain++;

                    }while(this->_board[piece_posX][piece_posY].getQueen() && (enemy_piece._x-x_chain>=0 || enemy_piece._x+x_chain<board_size || enemy_piece._y-y_chain>=0 || enemy_piece._y+y_chain<board_size));

                    moves.push_back(enemy_piece);

                }
            }
        }

        if(piece_posX>enemy_piece_cp._x && piece_posY<enemy_piece_cp._y) // top right
        {
            if(enemy_piece_cp._x-x>=0 && enemy_piece_cp._y+y<board_size)
            {
                if(!this->_board[enemy_piece_cp._x-x][enemy_piece_cp._y+y].getAlive())
                {
                    enemy_piece._x = enemy_piece_cp._x - x;
                    enemy_piece._y = enemy_piece_cp._y + y;
                    enemy_piece.isCapture = true;
                    enemy_piece.capture_count = enemy_piece.capture_count + 1;   
                    enemy_piece.captured_enemies.push_back(enemy_piece_cp);                


                    x_chain = 1;
                    y_chain = 1;

                    do{
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x-x_chain][enemy_piece._y-y_chain].getAlive() && this->_board[enemy_piece._x-x_chain][enemy_piece._y-y_chain].getColor() != color) // top left chain capture
                        {    
                            chain_capture._x = chain_capture._x - x_chain;
                            chain_capture._y = chain_capture._y - y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x-x_chain][enemy_piece._y+y_chain].getAlive() && this->_board[enemy_piece._x-x_chain][enemy_piece._y+y_chain].getColor() != color) // top right chain capture
                        {    
                            chain_capture._x = chain_capture._x - x_chain;
                            chain_capture._y = chain_capture._y + y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x+x_chain][enemy_piece._y+y_chain].getAlive() && this->_board[enemy_piece._x+x_chain][enemy_piece._y+y_chain].getColor() != color) // bottom right chain capture
                        {    
                            chain_capture._x = chain_capture._x + x_chain;
                            chain_capture._y = chain_capture._y + y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        //bottom left chain capture is not possible as capture was made from this direction

                        x_chain++;
                        y_chain++;

                    }while(this->_board[piece_posX][piece_posY].getQueen() && (enemy_piece._x-x_chain>=0 || enemy_piece._x+x_chain<board_size || enemy_piece._y-y_chain>=0 || enemy_piece._y+y_chain<board_size));

                    moves.push_back(enemy_piece);
                }
            }
        }

        if(piece_posX<enemy_piece_cp._x && piece_posY>enemy_piece_cp._y) // bottom left
        {
            
            if(enemy_piece_cp._x+x<board_size && enemy_piece_cp._y-y>=0)
            {
                if(!this->_board[enemy_piece_cp._x+x][enemy_piece_cp._y-y].getAlive())
                {
                    enemy_piece._x = enemy_piece_cp._x + x;
                    enemy_piece._y = enemy_piece_cp._y - y;
                    enemy_piece.isCapture = true;
                    enemy_piece.capture_count = enemy_piece.capture_count + 1;   
                    enemy_piece.captured_enemies.push_back(enemy_piece_cp);                

                    x_chain = 1;
                    y_chain = 1;

                    do{

                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x-x_chain][enemy_piece._y-y_chain].getAlive() && this->_board[enemy_piece._x-x_chain][enemy_piece._y-y_chain].getColor() != color) // top left chain capture
                        {    
                            chain_capture._x = chain_capture._x - x_chain;
                            chain_capture._y = chain_capture._y - y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x+x_chain][enemy_piece._y+y_chain].getAlive() && this->_board[enemy_piece._x+x_chain][enemy_piece._y+y_chain].getColor() != color) // bottom right chain capture
                        {    
                            chain_capture._x = chain_capture._x + x_chain;
                            chain_capture._y = chain_capture._y + y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }

                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x+x_chain][enemy_piece._y-y_chain].getAlive() && this->_board[enemy_piece._x+x_chain][enemy_piece._y-y_chain].getColor() != color) // bottom left chain capture
                        {    
                            chain_capture._x = chain_capture._x + x_chain;
                            chain_capture._y = chain_capture._y - y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        //top right chain capture is not possible as capture was made from this direction

                        x_chain++;
                        y_chain++;

                    }while(this->_board[piece_posX][piece_posY].getQueen() && (enemy_piece._x-x_chain>=0 || enemy_piece._x+x_chain<board_size || enemy_piece._y-y_chain>=0 || enemy_piece._y+y_chain<board_size));

                    moves.push_back(enemy_piece);
                }
            }
        }
        
        if(piece_posX<enemy_piece_cp._x && piece_posY<enemy_piece_cp._y) // bottom right
        {
            if(enemy_piece_cp._x+x<board_size && enemy_piece_cp._y+y<board_size)
            {
                if(!this->_board[enemy_piece_cp._x+x][enemy_piece_cp._y+y].getAlive())
                {
                    enemy_piece._x = enemy_piece_cp._x + x;
                    enemy_piece._y = enemy_piece_cp._y + y;
                    enemy_piece.isCapture = true;
                    enemy_piece.capture_count = enemy_piece.capture_count + 1;   
                    enemy_piece.captured_enemies.push_back(enemy_piece_cp);                


                    x_chain = 1;
                    y_chain = 1;

                    do{
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x-x_chain][enemy_piece._y+y_chain].getAlive() && this->_board[enemy_piece._x-x_chain][enemy_piece._y+y_chain].getColor() != color) // top right chain capture
                        {    
                            chain_capture._x = chain_capture._x - x_chain;
                            chain_capture._y = chain_capture._y + y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x+x_chain][enemy_piece._y+y_chain].getAlive() && this->_board[enemy_piece._x+x_chain][enemy_piece._y+y_chain].getColor() != color) // bottom right chain capture
                        {    
                            chain_capture._x = chain_capture._x + x_chain;
                            chain_capture._y = chain_capture._y + y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        
                        chain_capture = enemy_piece;
                        if(this->_board[enemy_piece._x+x_chain][enemy_piece._y-y_chain].getAlive() && this->_board[enemy_piece._x+x_chain][enemy_piece._y-y_chain].getColor() != color) // bottom left chain capture
                        {    
                            chain_capture._x = chain_capture._x + x_chain;
                            chain_capture._y = chain_capture._y - y_chain;
                            this->calc_captures(moves, enemy_piece._x, enemy_piece._y, chain_capture, color);
                        }
                        //top left chain capture is not possible as capture was made from this direction

                        x_chain++;
                        y_chain++;

                    }while(this->_board[piece_posX][piece_posY].getQueen() && (enemy_piece._x-x_chain>=0 || enemy_piece._x+x_chain<board_size || enemy_piece._y-y_chain>=0 || enemy_piece._y+y_chain<board_size));

                    moves.push_back(enemy_piece);
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
    MovePosition found_pos; // position of found piece
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


bool Board::isLost(short int piece_posX, short int piece_posY)
{
    short int enemyX;
    short int enemyY;
    bool found = false;


    // top left
    enemyX = piece_posX - 1;
    enemyY = piece_posY - 1;
    do
    {
        if(this->_board[enemyX][enemyY].getAlive() && this->_board[enemyX][enemyY].getColor() != this->_board[piece_posX][piece_posY].getColor())
            found = true;
        
        enemyY--;
        enemyX--;

    }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX>=0 && enemyY>=0 && !found);

    if(found)
    {
        enemyX = piece_posX+1;
        enemyY = piece_posY+1;

        do
        {
            if(!this->_board[enemyX][enemyY].getAlive())
                return true;
           
            enemyY++;
            enemyX++;
        }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX<8 && enemyY<8);
    }

    // top right
    enemyX = piece_posX - 1;
    enemyY = piece_posY + 1;
    
    do
    {
        if(this->_board[enemyX][enemyY].getAlive() && this->_board[enemyX][enemyY].getColor() != this->_board[piece_posX][piece_posY].getColor())     
            found = true;
        
        enemyY++;
        enemyX--;
    }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX>=0 && enemyY<8 && !found);

    if(found)
    {
        enemyX = piece_posX+1;
        enemyY = piece_posY-1;

        do
        {
            if(!this->_board[enemyX][enemyY].getAlive())
                return true;
            
            enemyY--;
            enemyX++;
        }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX<8 && enemyY>=0);
    }

    // bottom left
    enemyX = piece_posX + 1;
    enemyY = piece_posY - 1;
    
    do
    {
        if(this->_board[enemyX][enemyY].getAlive() && this->_board[enemyX][enemyY].getColor() != this->_board[piece_posX][piece_posY].getColor())
            found = true;
         
        enemyY--;
        enemyX++;
    }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX<8 && enemyY>=0 && !found);

    if(found)
    {
        enemyX = piece_posX-1;
        enemyY = piece_posY+1;

        do
        {
            if(!this->_board[enemyX][enemyY].getAlive())
                return true;

            enemyY++;
            enemyX--;
        }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX>=0 && enemyY<8);
    }

     // bottom right
    enemyX = piece_posX + 1;
    enemyY = piece_posY + 1;
    
    do
    {
        if(this->_board[enemyX][enemyY].getAlive() && this->_board[enemyX][enemyY].getColor() != this->_board[piece_posX][piece_posY].getColor())
            found = true;
        
        enemyY++;
        enemyX++;
    }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX<8 && enemyY<8 && !found);

    if(found)
    {
        enemyX = piece_posX-1;
        enemyY = piece_posY-1;

        do
        {
            if(!this->_board[enemyX][enemyY].getAlive())
                return true;

            enemyY--;
            enemyX--;
        }while(this->_board[piece_posX][piece_posY].getQueen() && enemyX>=0 && enemyY>=8);
    }
    
    return false;
}

