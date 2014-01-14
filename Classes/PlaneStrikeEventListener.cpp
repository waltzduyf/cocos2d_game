#include "PlaneStrikeEventListener.h"
#include "Airplane.h"
#include "Enviroment.h"

using namespace std;

void PlaneStrikeEventListener::onPlaneOverlap(Airplane* oldOne, Airplane* newOne)
{
    if (oldOne->color != newOne->color)
    {
        // ��ɫ��һ�����ǿ����
        newOne->fight(oldOne);
    }
}
