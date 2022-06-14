#ifndef POSITION_H
#define POSITION_H

#include <vector>

struct MovePosition
{
    short int _x; // x coordinate
    short int _y; // y coordinate
    bool isCapture; // tells if move is capturing move or not
    short int capture_count; // counts captures if chain capture occurs
    std::vector<MovePosition> captured_enemies; // stores data of captured enemies when capture occurs

    MovePosition(){isCapture = false; capture_count=0;}
};

#endif