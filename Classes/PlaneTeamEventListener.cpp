#include "PlaneTeamEventListener.h"

void PlaneTeamEventListener::onPlaneOverlap(Airplane* oldOne, Airplane* newOne)
{
    if (oldOne->color == newOne->color)
    {
        mergeTeam(oldOne, newOne);
    }
}

void PlaneTeamEventListener::mergeTeam(Airplane* oldOne, Airplane* newOne)
{
    vector<Airplane*> oldMem(oldOne->members);
    for (vector<Airplane*>::iterator it = oldMem.begin();
        it != oldMem.end(); it++)
    {
        Airplane* a = *it;
        a->leaveTeam();
        a->joinATeam(newOne);
    }
}