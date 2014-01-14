#ifndef __MOVEACTION__
#define __MOVEACTION__

#include "ChessBoardGrid.h"

class MoveAction
{
public:
    MoveAction(int type, ChessBoardGrid* from, ChessBoardGrid* to);

    int type;
    ChessBoardGrid* from;
    ChessBoardGrid* to;
};


#endif