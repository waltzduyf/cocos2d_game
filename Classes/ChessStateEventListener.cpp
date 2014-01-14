#include "ChessStateEventListener.h"
#include "Enviroment.h"

void ChessStateEventListener::onThrowingDiceEvent()
{
    Enviroment *env = Enviroment::getInstance();
    env->state = CHESS_BOARD_STATE_MOVE;
}

void ChessStateEventListener::onThrownDiceEvent(ThrownDiceEvent *e)
{
    Enviroment *env = Enviroment::getInstance();

    if (!env->canMoveAnyPlane())
    {
        env->turnNext();
    }
}

void ChessStateEventListener::onPlaneStop(PassGridEvent *e)
{
    if (e->airplane->isLeader())
    {
        Enviroment::getInstance()->turnNext();
    }
}
