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
    // 시작 위치의 타일 인덱스를 구함
    int startIdx = GetTileIndex(startPos);
    if (startIdx < 0)
        return;

    // 도착 위치의 타일 인덱스를 구함
    int goalIdx = GetTileIndex(destPos);
    if (goalIdx < 0)
        return;

    // 구한 타일 인덱스를 기반으로 길찾기 시작
    GET_SINGLE(AStar)->AstarStart(startIdx, goalIdx);
}


void DynamicObj::AStarMove()
{
    //// 목적지까지 최적 경로인 타일들의 인덱스를 갖는 목록을 가져옴
    list<int>* bestList = GET_SINGLE(AStar)->GetBestList();

    if (bestList == NULL || bestList->empty())
    {
        info.dir = D3DXVECTOR3(0, 0, 0);
        return;
    }

    auto tiles = GET_SINGLE(ObjMgr)->GetTiles();

    // 최적 경로 목록에서 맨 앞의 원소(이동할 타일 1개) 정보를 가져옴
    int destIdx = bestList->front();
    auto destPos = D3DXVECTOR3((*tiles)[destIdx]->posX, (*tiles)[destIdx]->posY, 0);
    
    // 목적지와 객체 사이 간의 변위를 구함
    auto displacement = destPos - info.pos;
    // 변위에서 크기만 가져옴
    float distance = D3DXVec3Length(&displacement);

    // 변위에서 방향만 가져옴
    D3DXVec3Normalize(&info.dir, &displacement);

    info.pos += info.dir * moveSpeed;

    // 타일 도착 판정을 위한 정지거리를 지정하여 검사
    if (distance < 5.f)
    {
        // 최적 경로 목록에서 첫번째 원소를 꺼냄
        bestList->pop_front();
    }
}
