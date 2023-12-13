#include "DynamicObj.h"
#include "Include.h"

DynamicObj::DynamicObj()
{
}

DynamicObj::DynamicObj(const INFO& info)
    :Object(info)
{
}

DynamicObj::~DynamicObj()
{
}

void DynamicObj::AStarStart(const D3DXVECTOR3& startPos, const D3DXVECTOR3& destPos)
{
    // ���� ��ġ�� Ÿ�� �ε����� ����
    int startIdx = GetTileIndex(startPos);
    if (startIdx < 0)
        return;

    // ���� ��ġ�� Ÿ�� �ε����� ����
    int goalIdx = GetTileIndex(destPos);
    if (goalIdx < 0)
        return;

    // ���� Ÿ�� �ε����� ������� ��ã�� ����
    GET_SINGLE(AStar)->AstarStart(startIdx, goalIdx);
}


void DynamicObj::AStarMove()
{
    //// ���������� ���� ����� Ÿ�ϵ��� �ε����� ���� ����� ������
    list<int>* bestList = GET_SINGLE(AStar)->GetBestList();

    if (bestList == NULL || bestList->empty())
    {
        info.dir = D3DXVECTOR3(0, 0, 0);
        return;
    }

    auto tiles = GET_SINGLE(ObjMgr)->GetTiles();

    // ���� ��� ��Ͽ��� �� ���� ����(�̵��� Ÿ�� 1��) ������ ������
    int destIdx = bestList->front();
    auto destPos = D3DXVECTOR3((*tiles)[destIdx]->posX, (*tiles)[destIdx]->posY, 0);
    
    // �������� ��ü ���� ���� ������ ����
    auto displacement = destPos - info.pos;
    // �������� ũ�⸸ ������
    float distance = D3DXVec3Length(&displacement);

    // �������� ���⸸ ������
    D3DXVec3Normalize(&info.dir, &displacement);

    info.pos += info.dir * moveSpeed;

    // Ÿ�� ���� ������ ���� �����Ÿ��� �����Ͽ� �˻�
    if (distance < 5.f)
    {
        // ���� ��� ��Ͽ��� ù��° ���Ҹ� ����
        bestList->pop_front();
    }
}
