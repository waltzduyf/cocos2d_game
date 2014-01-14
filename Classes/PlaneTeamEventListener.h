#ifndef __PlaneTeamEventListener__
#define __PlaneTeamEventListener__

#include "PlaneOverlapEventListener.h"

class PlaneTeamEventListener : public PlaneOverlapEventListener
{
public:
    virtual void onPlaneOverlap(Airplane* oldOne, Airplane* newOne);
private:
    void mergeTeam(Airplane* oldOne, Airplane* newOne);
};


#endif