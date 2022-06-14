#include "../inc/Piece.h"



Piece::Piece()
{
    this->_isQueen = false;
    this->_isAlive = false;
    this->_isWhite = false;
}

void swap(Piece& a, Piece& b)
{   
    Piece tmp = a;
    a = b;
    b = tmp;
}

bool Piece::operator==(const Piece& a)const
{
    bool isEqual = true;
    
    if(this->_isAlive != a._isAlive)
        isEqual = false;
    
    if(this->_isQueen != a._isQueen)
        isEqual = false;
    
    if(this->_isWhite != a._isWhite)
        isEqual = false;

    return isEqual;
}
