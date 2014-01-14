#include "PlaneStrikeEventListener.h"
#include "Airplane.h"
#include "Enviroment.h"

using namespace std;

void PlaneStrikeEventListener::onPlaneOverlap(Airplane* oldOne, Airplane* newOne)
{
    if (oldOne->color != newOne->color)
    {
        // 颜色不一样，那开打吧
        newOne->fight(oldOne);
    }
}
