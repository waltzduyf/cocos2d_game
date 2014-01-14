#include "ChessBoardGrid.h"


ChessBoardGrid::ChessBoardGrid(int id, CCPoint* position, int color = FORCE_COLOR_NULL, int type = CHESS_BOARD_GRID_TYPE_NORMAL)
    : next(0), autoJump(true)
{
    this->id = id;
    this->position = position;
    this->color = color;
    this->type = type;
}


ChessBoardGrid::~ChessBoardGrid(void)
{
    delete position;
}
