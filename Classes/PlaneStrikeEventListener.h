#ifndef __PLANESTRIKEEVENTLISTENER__
#define __PLANESTRIKEEVENTLISTENER__

#include "PlaneOverlapEventListener.h"

class PlaneStrikeEventListener : public PlaneOverlapEventListener
{
public:
    virtual void onPlaneOverlap(Airplane* oldOne, Airplane* newOne);
};

#endif