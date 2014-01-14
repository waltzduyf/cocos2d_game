#ifndef __ENVIROMENT__
#define __ENVIROMENT__

#include "ChessBoard.h"
#include "ChessBoardScene.h"

class Enviroment
{
private:
    Enviroment(void);

    static Enviroment* m_INSTANCE;

    bool currentPlayerHasFlyingPlane();
public:

    static Enviroment* getInstance();

    // �ֵ���һ����ɫ
    void turnNext();

    // �������
    int playerNum;
    // ���������
    CircularLinkedList<int> players;
    // ��Щ��AI
    map<int, bool> AIMap;

    // Ŀǰ���ĸ���ɫ�Ļغ�
    int currentColor;

    // ����״̬
    int state;

    // Ͷ�ĵ���
    int currentPoint;
    // ��ǰ�����������
    ChessBoard* currentChessBoard;

    ChessBoardScene* mainScene;

    // �Ƿ���Կ���
    bool isCanControl;

    // ��ǰ����Ƿ��ܹ��ƶ��κηɻ�
    bool canMoveAnyPlane();

    // ��ǰ����Ƿ���AI
    bool isCurrentPlayerAI();
};

#endif
