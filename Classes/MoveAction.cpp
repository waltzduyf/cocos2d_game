#include "MoveAction.h"

MoveAction::MoveAction(int type, ChessBoardGrid* from, ChessBoardGrid* to)
{
    this->type = type;
    this->from = from;
    this->to = to;
}
