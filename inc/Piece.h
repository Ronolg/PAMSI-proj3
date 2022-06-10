#ifndef PIECE_H
#define PIECE_H

#include <iostream>


class Piece
{
    private:
        bool _isQueen;
        bool _isAlive;
        bool _isWhite;
    
    public:
        Piece();

        bool getAlive() const {return this->_isAlive;};
        bool getColor() const {return this->_isWhite;};
        bool getQueen() const {return this->_isQueen;};


        void setAlive(bool a){this->_isAlive = a;};
        void setColor(bool a){this->_isWhite = a;};
        void setQueen(bool a){this->_isQueen = a;};

        
        bool operator==(const Piece& a)const;
};

void swap(Piece& a, Piece& b);


#endif