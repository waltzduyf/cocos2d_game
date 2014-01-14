#include "PassGridEvent.h"


PassGridEvent::PassGridEvent(Airplane* airplane, bool isJumped)
{
    this->airplane = airplane;
    this->isJumped = isJumped;
}


PassGridEvent::~PassGridEvent(void)
{
}
