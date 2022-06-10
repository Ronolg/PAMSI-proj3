#include "../inc/Player.h"


Player::Player(Board& board, bool color)
{
    short int j;
    short int k;

    this->_player_pieces = max_pieces;

    if(color)
    {
        j = board_size/2 + 1;
        k = 0;
    }
    else
    {
        j = 0;
        k = 1;
    }
    
    for(int i = 0; i<max_pieces; i++)
    {
        if(k<board_size)
        {
            board._board[j][k].setAlive(true);
            board._board[j][k].setColor(color);

            k+=2;
        }
        else 
        {
            i--;
            j++;
            
            if(j%2 == 0)
                k = 1;
            else
                k = 0;
        }    
    }
}

bool Player::check_selected_piece(Board& board, short int x, short int y, bool color) const
{
    if(board._board[x][y].getAlive() && board._board[x][y].getColor()==color)
    {
        if(x>0 && y>0)
        {
            if(board._board[x-1][y-1].getAlive())
            {
                if(board._board[x-1][y-1].getColor()!=color) 
                {
                    if(x-1>0 && y-1>0)
                    {
                        if(!board._board[x-2][y-2].getAlive())
                            return true;
                    }
                }
            }
            else 
                return true;
        }  
        
        if(x>0 && y<7)
        {
            if(board._board[x-1][y+1].getAlive())
            {
                if(board._board[x-1][y+1].getColor()!=color)   
                {
                    if(x-1>0 && y+1<7)
                    {
                        if(!board._board[x-2][y+2].getAlive())
                            return true;
                    }
                }  
            }
            else 
                return true;
        }
        
        if(x<7 && y>0)
        {
            if(board._board[x+1][y-1].getAlive())
            {
                if(board._board[x+1][y-1].getColor()!=color)
                {
                    if(x+1<7 && y-1>0)
                    {
                        if(!board._board[x+2][y-2].getAlive())
                            return true;
                    }
                }
            }
            else
                return true;
        }
        
        if(x<7 && y<7)
        {
            if(board._board[x+1][y+1].getAlive())
            {
                if(board._board[x+1][y+1].getColor()!=color)  
                {
                    if(x+1<7 && y+1<7)
                    {
                        if(!board._board[x+2][y+2].getAlive())
                            return true;
                    }
                }  
            }
            else 
                return true;
        }
       
    } 

    //std::cout << "Wrong pick, try again." << std::endl;
    return false;
}

bool Player::check_chain_capture(Board& board, short int x, short int y, bool color) const
{
    if(x>0 && y>0)
    {
        if(board._board[x-1][y-1].getAlive())
        {
            if(board._board[x-1][y-1].getColor()!=color) 
            {
                if(x-1>0 && y-1>0)
                {
                    if(!board._board[x-2][y-2].getAlive())
                        return true;
                }
            }
        }
    }  
    
    if(x>0 && y<7)
    {
        if(board._board[x-1][y+1].getAlive())
        {
            if(board._board[x-1][y+1].getColor()!=color)   
            {
                if(x-1>0 && y+1<7)
                {
                    if(!board._board[x-2][y+2].getAlive())
                        return true;
                }
            }  
        }
    }
    
    if(x<7 && y>0)
    {
        if(board._board[x+1][y-1].getAlive())
        {
            if(board._board[x+1][y-1].getColor()!=color)
            {
                if(x+1<7 && y-1>0)
                {
                    if(!board._board[x+2][y-2].getAlive())
                        return true;
                }
            }
        }
       
    }
    
    if(x<7 && y<7)
    {
        if(board._board[x+1][y+1].getAlive())
        {
            if(board._board[x+1][y+1].getColor()!=color)  
            {
                if(x+1<7 && y+1<7)
                {
                    if(!board._board[x+2][y+2].getAlive())
                        return true;
                }
            }  
        }
    }
       
    return false;
}

bool Player::check_selected_pos(Board& board, short int piece_posX, short int piece_posY, short int desiredX, short int desiredY) const
{
    short int piece_posX_copy = piece_posX;
    short int piece_posY_copy = piece_posY;
    
    bool pieceIntheWay[all_directions]; //true if there is piece with the same color as queen for specific direction
    short int direction = -1;   // 0 -> top left, 1 -> top right, 2 -> bottom left, 3 -> bottom right, -1 -> direction not specified

    for(int i; i<all_directions; i++) //
        pieceIntheWay[i] = false;     // by default there is no piece in the way

    if(piece_posX > desiredX && piece_posY > desiredY)
    {
        do
        { 
            // checking top left tile
            if(board._board[piece_posX_copy-1][piece_posY_copy-1].getAlive())
            {
                
                if(board._board[piece_posX_copy-1][piece_posY_copy-1].getColor()!=board._board[piece_posX][piece_posY].getColor()) 
                {
                    if(piece_posX_copy-1>0 && piece_posY_copy-1>0)
                    {
                        if(!board._board[piece_posX_copy-2][piece_posY_copy-2].getAlive())
                        {    
                            if(desiredX == piece_posX_copy-2 && desiredY == piece_posY_copy-2)
                                direction=0;
                        }
                        else
                        {
                            std::cout <<"Wrong move, cannot take more than one piece with one move."<< std::endl;
                            return false;
                        }
                    }
                }
                else
                    pieceIntheWay[0]=true;

            }
            else // move without capture if white or if piece is a queen
            {
                if(board._board[piece_posX][piece_posY].getColor() || board._board[piece_posX][piece_posY].getQueen())
                {
                    if(desiredX == piece_posX_copy-1 && desiredY == piece_posY_copy-1)
                        direction=0;
                }
            }

            piece_posX_copy--;
            piece_posY_copy--;


        }while(board._board[piece_posX][piece_posY].getQueen() && piece_posX_copy>0 && piece_posY_copy>0 && direction!=0);
    }
    piece_posX_copy = piece_posX;
    piece_posY_copy = piece_posY;
    
    if(piece_posX > desiredX && piece_posY < desiredY)
    {
        do
        {// checking top right tile
            if(board._board[piece_posX_copy-1][piece_posY_copy+1].getAlive())
            {
                if(board._board[piece_posX_copy-1][piece_posY_copy+1].getColor()!=board._board[piece_posX][piece_posY].getColor()) 
                {
                    if(piece_posX_copy-1>0 && piece_posY_copy+1<board_size)
                    {
                        if(!board._board[piece_posX_copy-2][piece_posY_copy+2].getAlive())
                        {    
                            if(desiredX == piece_posX_copy-2 && desiredY == piece_posY_copy+2)
                                direction=1;
                        }
                        else 
                        {
                            
                            std::cout <<"sraka Wrong move, cannot take more than one piece with one move."<< std::endl;
                            return false;
                        }
                    }
                }
                else
                    pieceIntheWay[1]=true;
            }
            else // move without capture if white or if piece is a queen
            {
                if(board._board[piece_posX][piece_posY].getColor() || board._board[piece_posX][piece_posY].getQueen())
                {
                    if(desiredX == piece_posX_copy-1 && desiredY == piece_posY_copy+1)
                        direction=1;
                }
            }
            
            piece_posX_copy--;
            piece_posY_copy++;
        
        }while(board._board[piece_posX][piece_posY].getQueen() && piece_posX_copy>0 && piece_posY_copy<board_size && direction!=1);
    }

    piece_posX_copy = piece_posX;
    piece_posY_copy = piece_posY;
    
    if(piece_posX < desiredX && piece_posY > desiredY)
    {
        do
        {
            // checking bottom left tile
            if(board._board[piece_posX_copy+1][piece_posY_copy-1].getAlive())
            {
                if(board._board[piece_posX_copy+1][piece_posY_copy-1].getColor()!=board._board[piece_posX][piece_posY].getColor()) 
                {
                    if(piece_posX_copy+1<board_size && piece_posY_copy-1>0)
                    {
                        if(!board._board[piece_posX_copy+2][piece_posY_copy-2].getAlive())
                        {    
                            if(desiredX == piece_posX_copy+2 && desiredY == piece_posY_copy-2)
                                direction=2;
                        }
                        else 
                        {
                            std::cout <<"Wrong move, cannot take more than one piece with one move."<< std::endl;
                            return false;
                        }
                    }
                }
                else
                    pieceIntheWay[2]=true;
            }
            else // move without capture if black or if piece is a queen
            {
                if(!board._board[piece_posX][piece_posY].getColor() || board._board[piece_posX][piece_posY].getQueen())
                {
                    if(desiredX == piece_posX_copy+1 && desiredY == piece_posY_copy-1)
                        direction=2;
                }
            }

            piece_posX_copy++;
            piece_posY_copy--;

        }while(board._board[piece_posX][piece_posY].getQueen() && piece_posX_copy<board_size && piece_posY_copy>0 && direction!=2);
    }

    piece_posX_copy = piece_posX;
    piece_posY_copy = piece_posY;

    if(piece_posX < desiredX && piece_posY < desiredY)
    {
        do{
            // checking bottom right tile
            if(board._board[piece_posX_copy+1][piece_posY_copy+1].getAlive())
            {
                if(board._board[piece_posX_copy+1][piece_posY_copy+1].getColor()!=board._board[piece_posX][piece_posY].getColor()) 
                {
                    if(piece_posX_copy+1<board_size && piece_posY_copy+1<board_size)
                    {
                        if(!board._board[piece_posX_copy+2][piece_posY_copy+2].getAlive())
                        {    
                            if(desiredX == piece_posX_copy+2 && desiredY == piece_posY_copy+2)
                                direction=3;
                        }
                        else
                        {
                            std::cout <<"Wrong move, cannot take more than one piece with one move."<< std::endl;
                            return false;
                        }
                    }
                }
                else 
                    pieceIntheWay[3]=true;
            }
            else // move without capture if black or if piece is a queen
            {
                if(!board._board[piece_posX][piece_posY].getColor() || board._board[piece_posX][piece_posY].getQueen())
                {
                    if(desiredX == piece_posX_copy+1 && desiredY == piece_posY_copy+1)
                        direction=3;
                }
            }

            piece_posX_copy++;
            piece_posY_copy++;

        }while(board._board[piece_posX][piece_posY].getQueen() && piece_posX_copy<board_size && piece_posY_copy<board_size && direction!=3);
    }
    
    switch (direction)
    {
    case -1:
        std::cout << "Illegal move! Try again:" << std::endl;
        return false;
        
        break;

    case 0: // top left
        if(pieceIntheWay[0] || !check_multi_capture(board, piece_posX, piece_posY, desiredX, desiredY, direction))
        {
            std::cout << "Illegal move! Try again:" << std::endl;
            return false;
        }
        else
            return true;

    case 1: // top right
        if(pieceIntheWay[1] || !check_multi_capture(board, piece_posX, piece_posY, desiredX, desiredY, direction))
        {
            std::cout << "Illegal move! Try again:" << std::endl;
            return false;
        }
        else
            return true;
        
    case 2: // bottom left
        if(pieceIntheWay[2] || !check_multi_capture(board, piece_posX, piece_posY, desiredX, desiredY, direction))
        {
            std::cout << "Illegal move! Try again:" << std::endl;
            return false;
        }
        else
            return true;

    case 3: // bottom right
        if(pieceIntheWay[3] || !check_multi_capture(board, piece_posX, piece_posY, desiredX, desiredY, direction))
        {
            std::cout << "Illegal move! Try again:" << std::endl;
            return false;
        }
        else
            return true;
    
    default:
        std::cout << "Unknown behaviour" << std::endl;
        return false;
        
        break;
    }

}

bool Player::capture(Board& board, Player& enemyPlayer, short int starting_x, short int starting_y, short int desired_x, short int desired_y) const
{
    short int enemyX = starting_x;
    short int enemyY = starting_y;
    
    if(board._board[starting_x][starting_y].getQueen())
    { // capturing as a queen
        if(starting_x>desired_x && starting_y>desired_y)// top left 
        {
            do{
                enemyX--;
                enemyY--;
            }while(!board._board[enemyX][enemyY].getAlive() && enemyX>desired_x && enemyY>desired_y);

            // checking if queen does not attempt to capture more than 1 piece with one move.
            
            if(!check_multi_capture(board, enemyX, enemyY, desired_x, desired_y, 0))
                return false;
        }

        if(starting_x>desired_x && starting_y<desired_y)// top right
        {
            do{
                enemyX--;
                enemyY++;
            }while(!board._board[enemyX][enemyY].getAlive() && enemyX>desired_x && enemyY<desired_y);

            // checking if queen does not attempt to capture more than 1 piece with one move.
            if(!check_multi_capture(board, enemyX, enemyY, desired_x, desired_y, 1))
                return false;
        }

        if(starting_x<desired_x && starting_y>desired_y)// bottom left
        {
            do{
                enemyX++;
                enemyY--;
            }while(!board._board[enemyX][enemyY].getAlive() && enemyX<desired_x && enemyY>desired_y);

            // checking if queen does not attempt to capture more than 1 piece with one move.
            if(!check_multi_capture(board, enemyX, enemyY, desired_x, desired_y, 2))
                return false;

        }

        if(starting_x<desired_x && starting_y<desired_y)// bottom right
        {
            do{
                enemyX++;
                enemyY++;
            }while(!board._board[enemyX][enemyY].getAlive() && enemyX<desired_x && enemyY<desired_y);

            // checking if queen does not attempt to capture more than 1 piece with one move.
            if(!check_multi_capture(board, enemyX, enemyY, desired_x, desired_y, 3))
                return false;

        }
    }
    else // capturing as a regular piece
    {
        if(starting_x>desired_x)
            enemyX--;
        else
            enemyX++;
        
        if(starting_y>desired_y)
            enemyY--;
        else
            enemyY++;
    }


    if(board._board[enemyX][enemyY].getAlive())
    {
        if(board._board[enemyX][enemyY].getColor()!=board._board[starting_x][starting_y].getColor())
        {
            board._board[enemyX][enemyY].setAlive(false);
            enemyPlayer.setPlayerPieces(enemyPlayer.getPlayerPieces()-1);
            return true;
        }
    }    

    
    std::cout << "Wrong capturing behaviour" << std::endl;
    return false;

}

bool Player::check_multi_capture(Board& board, short int starting_x, short int starting_y, short int desired_x, short int desired_y, unsigned short int direction) const
{
    short int x;   
    short int y;    
    unsigned int count = 0;
    switch (direction)
    {
    case 0:
        x = starting_x-1; y = starting_y-1;
        while(x>desired_x && y>desired_y)
        {
            if(board._board[x][y].getAlive())
                count++;
                
            x--; y--;
        }
        break;

    case 1:
        x = starting_x-1; y = starting_y+1;
        while(x>desired_x && y<desired_y)
        {
            if(board._board[x][y].getAlive())
                count++;

            x--; y++;
        }
        break;

    case 2:
        x = starting_x+1; y = starting_y-1;
        while(x<desired_x && y>desired_y)
        {
            if(board._board[x][y].getAlive())
                count++;

            x++; y--;
        }
        break;

    case 3:
        x = starting_x+1; y = starting_y+1;
        while(x<desired_x && y<desired_y)
        {
            if(board._board[x][y].getAlive())
                count++;

            x++; y++;
        }
        break;
    
    default:
        std::cout << "Unknown direction" << std::endl;
        return false;
        break;
    }

    if(count>1)
        return false;
    
    return true;
}
