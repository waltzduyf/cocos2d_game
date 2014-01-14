#include "Enviroment.h"
#include "PlaneChessEventManager.h"


Enviroment::Enviroment(void) : currentChessBoard(0), isCanControl(false), currentColor(0), currentPoint(0), state(CHESS_BOARD_STATE_THROW)
{
}

Enviroment* Enviroment::m_INSTANCE = 0;

Enviroment* Enviroment::getInstance()
{
    if (m_INSTANCE == 0)
    {
        m_INSTANCE = new Enviroment();
    }
    return m_INSTANCE;
}

void Enviroment::turnNext()
{
    this->mainScene->resetDice();

    this->state = CHESS_BOARD_STATE_THROW;
    if (this->currentPoint == 6)
    {
        this->isCanControl = true;
        PlaneChessEventManager::getInstance()->notifyTurnBegin();
        return;
    }

    if (this->currentColor == 0)
    {
        this->currentColor = players.getCurrent();
    }
    else
    {
        this->currentColor = players.next();
    }
    
    this->isCanControl = true;
    this->mainScene->showTurn(this->currentColor);
    PlaneChessEventManager::getInstance()->notifyTurnBegin();
}

bool Enviroment::canMoveAnyPlane()
{
    return this->currentPoint == 6
        || currentPlayerHasFlyingPlane();
}

bool Enviroment::currentPlayerHasFlyingPlane()
{
    int color = this->currentColor;
    vector<Airplane*> &planes = this->currentChessBoard->planes;
    vector<Airplane*>::iterator it = planes.begin();
    while (it != planes.end())
    {
        Airplane* plane = *it;
        if (plane->color == color 
            && (plane->state == STATE_FLYING || plane->state == STATE_READY))
        {
            return true;
        }
        it++;
    }

    return false;
}

bool Enviroment::isCurrentPlayerAI()
{
    return AIMap.at(this->currentColor);
}