#include "../inc/Board.h"
#include "../inc/Player.h"
#include "../inc/Piece.h"
#include "../inc/GameTree.h"
#include "../inc/Position.h"


// return absolute value of param: a
int abs(int a)
{
    return (a<0) ? -a : a;    
}

/*  Reads piece selection by player
    
    Parameters:
        board - game board on which pieces are located
        player - describes for which player selection read is made
        x, y - cords of selected piece
        color - color of selected piece

*/
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


/*  Reads position to move to
    
    Parameters:
        board - game board on which pieces are located
        player - describes for which player move read is made
        x, y - cords of selected piece
        desired x, desired y - cords of position the piece is supposed to move to
        color - color of selected piece

*/
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
    const unsigned int predicted_moves = 6;
    unsigned int moves = 0;
    
    // Parameters used for calculating the best move
    std::vector<std::shared_ptr<GameTree>> best_move_path;
    int min;

    const bool white = 1;
    const bool black = 0;
    short int x,y;                  // starting position of selected piece
    short int desired_x, desired_y; // position of selected piece after a move
    
    bool chain_capture;             // variable used to determine whether chain capture occurs or not 
    bool white_won = false;
    bool black_won = false;
  
    
    root->create(game_board, predicted_moves, player_white, player_black);
    

    // CHECKERS HUMAN VS AI ==================================================
    while(!white_won && !black_won)
    {
        if(moves == predicted_moves) // create game_tree for next moves
        {
            root = nullptr;
            root = std::make_shared<GameTree>(game_board);
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
                    game_board._board[desired_x][desired_y].setQueen(true);// make a queen

                system("clear");      //
                game_board.print();   // update the board

                if(player_white.check_chain_capture(game_board, desired_x, desired_y, white)) //checks if chain capture is possible
                {
                    x = desired_x;
                    y = desired_y;

                    do{// read another capturing move
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

        system("clear");
        moves++; // white's move has been made 
        
        
        
        // AI black player =================
        searched = root->search_for(game_board); // search for the move
        if(searched == nullptr)
            std::cout << "Nothing found" << std::endl;
        

        min = 10000;
        best_move_path.clear();
        auto tmp = best_move_path;
        searched->find_best_move(min, best_move_path, tmp); // calculates best move
        game_board = best_move_path[1]->move_board; // switch game board with the best move (with the lowest move value)
        
        game_board.print();
        system("clear");    

        moves++; // black's move has been made 
        
        player_white.setPlayerPieces(game_board.count_pieces(white)); // count white pieces
        player_black.setPlayerPieces(game_board.count_pieces(black)); // count black pieces
        
        if(player_black.getPlayerPieces()==0)
            white_won = true;

        if(player_white.getPlayerPieces()==0)
            black_won = true;


    }

    system("clear");    

    if(black_won)
        std::cout << "Blacks won!" << std::endl;
    if(white_won)
        std::cout << "Whites won!" << std::endl;
 
    
    return 0;
}
