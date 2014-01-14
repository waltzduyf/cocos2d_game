#include "PlaneOverlapEventListener.h"
#include "Enviroment.h"

void PlaneOverlapEventListener::onPlaneStop(PassGridEvent *e)
{
    Airplane* p = e->airplane;

    if (!p->isLeader())
    {
        return;
    }

    vector<Airplane*> &planes = Enviroment::getInstance()->currentChessBoard->planes;

    vector<Airplane*>::iterator it = planes.begin();

    while (it != planes.end())
    {
        Airplane* temp = *it;
        if (temp->isLeader() && temp != p
            && temp->position == p->position)
        {
            onPlaneOverlap(temp, e->airplane);
        }
        it++;
    }
}