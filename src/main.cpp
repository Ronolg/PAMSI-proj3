#include "../inc/Board.h"
#include "../inc/Player.h"
#include "../inc/Piece.h"
#include "../inc/AIplayer.h"
#include "../inc/GameTree.h"
#include "../inc/Position.h"


int abs(int a)
{
    return (a<0) ? -a : a;    
}


void read_piece_selection(Board& board, Player& player, short int& x, short int& y, bool color)
{
    do{
            if(color)
                std::cout << "Whites: Pick a piece by its cords: ";
            else
                std::cout << "Blacks: Pick a piece by its cords: ";

            std::cin >> x >> y;
        }while(!player.check_selected_piece(board,x,y,color));

        std::cout << std::endl;
}

void read_move_position(Board& board, Player& player, short int& x, short int& y, short int& desired_x, short int& desired_y, bool color)
{
    do{
        if(color)
            std::cout << "Whites: Pick desired location by its cords: ";
        else
            std::cout << "Blacks: Pick desired location by its cords: ";
        std::cin >> desired_x >> desired_y;
    }while(!player.check_selected_pos(board, x, y, desired_x, desired_y));
}

int main()
{
    Board game_board;
    Player player_white(game_board,true); // human player
    Player player_black(game_board,false); // AI player
    std::shared_ptr<GameTree> root = std::make_shared<GameTree>(game_board);
    std::shared_ptr<GameTree> searched;
    const unsigned int predicted_moves = 2;
    unsigned int moves = 0;

    const bool white = 1;
    const bool black = 0;
    short int x,y;                  // starting position of selected piece
    short int desired_x, desired_y; // position of selected piece after a move
    
    bool chain_capture;
    bool white_won = false;
    bool black_won = false;
    
    
    

    // CHECKERS HUMAN VS AI ==================================================
    while(!white_won && !black_won)
    {
        if(moves == predicted_moves) // create game_tree for next moves
        {
            root = nullptr;
            root->create(game_board, predicted_moves, player_white, player_black);
            moves = 0;
        }
        
        chain_capture = true;
        game_board.print();
        
        // WHITES
        read_piece_selection(game_board, player_white, x, y, white);
        read_move_position(game_board, player_white, x, y, desired_x, desired_y, white);
       

        if(abs(desired_x - x)>1) // checks if move is capturing move or not
        {
            while(chain_capture)
            {
                player_white.capture(game_board, player_black, x, y, desired_x, desired_y); // capture enemy piece
                swap(game_board._board[x][y], game_board._board[desired_x][desired_y]); // move to selected location

                if(desired_x==0)
                    game_board._board[desired_x][desired_y].setQueen(true);

                system("clear"); //
                game_board.print();   // update the board

                if(player_white.check_chain_capture(game_board, desired_x, desired_y, white)) //checks if chain capture is possible
                {
                    x = desired_x;
                    y = desired_y;

                    do{
                        std::cout << "Another capture is possible, please make a move" << std::endl;
                        std::cout << "Whites: Pick location of next capture by its cords: ";
                        std::cin >> desired_x >> desired_y;
                    }while(!player_white.check_selected_pos(game_board, x, y, desired_x, desired_y) || !(abs(desired_x - x)>1) || !player_white.capture(game_board, player_black, x, y, desired_x, desired_y));
                }
                else 
                    chain_capture = false;

               
            }
        }
        else
            swap(game_board._board[x][y], game_board._board[desired_x][desired_y]); 
            
        //make a white Queen
        if(desired_x==0)
            game_board._board[desired_x][desired_y].setQueen(true);

        if(player_black.getPlayerPieces()==0)
            black_won = true;

        system("clear");      //
        game_board.print();   // update the board
        
        moves++; // white's move has been made 
        
        // AI black player
        searched = root->search_for(game_board);
    
        if(searched != nullptr)
            searched->move_board.print();
        else
        std::cout << "Nothing found" << std::endl;
    

        moves++; // black's move has been made 

    }



    if(black_won)
        std::cout << "Blacks won!" << std::endl;
    if(white_won)
        std::cout << "Whites won!" << std::endl;

    
    return 0;
}


// BLACKS -> HUMAN
        /*do{
            std::cout << "Blacks: Pick a piece by its cords: ";
            std::cin >> x >> y;
        }while(!player_black.check_selected_piece(board,x,y,black));

        std::cout << std::endl;
        do{
            std::cout << "Blacks: Pick desired location by its cords: ";
            std::cin >> desired_x >> desired_y;
        }while(!player_black.check_selected_pos(board, x, y, desired_x, desired_y));

        if(abs(desired_x - x)>1)
        {
            player_black.capture(board, player_white, x, y, desired_x, desired_y);
            
        }
        swap(board._board[x][y], board._board[desired_x][desired_y]);
        system("clear");

        
        //make a black Queen
        if(desired_x==board_size-1)
            board._board[desired_x][desired_y].setQueen(true);


        if(player_white.getPlayerPieces()==0)
            white_won = true;
      
    }*/

// PRINTING GAMETREE ==================================================
    /* Board board;
    int a;
    Player white(board,true);
    Player black(board,false);

    std::shared_ptr<GameTree> root = std::make_shared<GameTree>(board);

    root->create(board, 2, white, black);
    
    std::cout << "ROOT BOARD" <<std::endl;
    root->move_board.print();
    std::cout << "============" <<std::endl;
    std::cout << std::endl <<std::endl;
 
    int i = 1;
    for(auto it = root->leaves.begin(); it!=root->leaves.end(); it++)
    {
        std::cout << i <<std::endl;

        (**it).move_board.print();
        
        if(!(**it).leaves.empty())
        {
            for(auto it2 = (**it).leaves.begin(); it2!=(**it).leaves.end(); it2++)
            {
                (**it2).move_board.print();
                i++;
            }
        
        }
        std::cout << std::endl <<std::endl;
        i++;
        std::cin >> a;
    }
    std::cout << i <<std::endl;
    std::cout << std::endl <<std::endl; */
