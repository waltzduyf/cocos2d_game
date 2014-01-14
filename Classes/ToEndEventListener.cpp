#include "ToEndEventListener.h"
#include "Enviroment.h"

void ToEndEventListener::onPassNormalGridEvent(PassGridEvent *e)
{
    if (e->airplane->position->type == CHESS_BOARD_GRID_TYPE_END
        && e->airplane->remainStep != 0)
    {
        e->airplane->direction = DIRECT_BACK;
    }
}

void ToEndEventListener::onPlaneStop(PassGridEvent *e)
{
    // 飞机一停下来，就把方向改过来
    e->airplane->direction = DIRECT_FORWARD;
    if (e->airplane->position->type == CHESS_BOARD_GRID_TYPE_END)
    {
        e->airplane->complete();
    }
}
