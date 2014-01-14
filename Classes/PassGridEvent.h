#ifndef __PASS_GRID_EVENT__
#define __PASS_GRID_EVENT__

#include "ChessBoardGrid.h"
#include "Airplane.h"
#include "PCEvent.h"

class PassGridEvent : public PCEvent
{
public:
    Airplane* airplane;
    // �Ƿ񾭹���������Ծ
    bool isJumped;
    
    PassGridEvent(Airplane* airplane, bool isJumped);
    ~PassGridEvent(void);
};

#endif