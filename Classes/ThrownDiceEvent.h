#ifndef __THROWNDICEEVENT__
#define __THROWNDICEEVENT__

#include "PCEvent.h"

class ThrownDiceEvent : public PCEvent
{
public:
    int point;

    ThrownDiceEvent();
    ~ThrownDiceEvent();

private:

};

#endif