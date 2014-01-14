#ifndef __PLANEOVERLAPEVENTLISTENER__
#define __PLANEOVERLAPEVENTLISTENER__

#include "PlaneChessEventListener.h"

class PlaneOverlapEventListener : public PlaneChessEventListener
{
public:
    virtual void onPlaneStop(PassGridEvent *e);
    virtual void onPlaneOverlap(Airplane* oldOne, Airplane* newOne) {}
private:

};

#endif