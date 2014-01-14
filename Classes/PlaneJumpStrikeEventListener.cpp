#include "PlaneJumpStrikeEventListener.h"
#include "Enviroment.h"

void PlaneJumpStrikeEventListener::onPassNormalGridEvent(PassGridEvent *e)
{
    if (!e->isJumped)
    {
        return;
    }

    Airplane* p = e->airplane;
    map<ChessBoardGrid*, ChessBoardGrid*> &jumpMap = Enviroment::getInstance()->currentChessBoard->longJumpMaps;

    map<ChessBoardGrid*, ChessBoardGrid*>::iterator rsIt = jumpMap.find(p->lastPosition);
    if (rsIt == jumpMap.end() || (*rsIt).second != p->position)
    {
        return;
    }

    vector<Airplane*> &planes = Enviroment::getInstance()->currentChessBoard->planes;
    map<ChessBoardGrid*, ChessBoardGrid*> &jumpFightMap = Enviroment::getInstance()->currentChessBoard->longJumpFightMaps;
    ChessBoardGrid* fightGrid = jumpFightMap.at(p->lastPosition);
    FOREACH_PLANES(planes)
    {
        Airplane* temp = *it;
        if (temp->position == fightGrid)
        {
            p->fight(temp);
            break;
        }
    }
}