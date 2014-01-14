#ifndef __CHESS_BOARD_GRID__
#define __CHESS_BOARD_GRID__

#include "PlaneChessConsts.h"
#include "cocos2d.h"

USING_NS_CC;

/************************************************************************/
/* �����ϵĸ��� */
/************************************************************************/
class ChessBoardGrid
{
public:
    int id;
    // �������ڵ�λ��
    CCPoint *position;
    // ���ӵ���ɫ
    int color;
    // ���ӵ�����
    int type;
    // �Ƿ��Զ�����Ծ����
    bool autoJump;
    // ��һ������
    ChessBoardGrid* pre;
    // ��һ������
    ChessBoardGrid* next;

    ChessBoardGrid(int id, CCPoint* position, int type, int color);
    ~ChessBoardGrid(void);
};

#endif