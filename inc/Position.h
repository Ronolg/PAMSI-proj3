#ifndef POSITION_H
#define POSITION_H

struct MovePosition
{
    short int _x;
    short int _y;
    bool isCapture;

    MovePosition(){isCapture = false;}
};

#endif