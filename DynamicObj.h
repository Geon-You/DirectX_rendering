#pragma once
#include "Object.h"
class DynamicObj abstract :
    public Object
{
public:
    DynamicObj();
    DynamicObj(const INFO& info);
    virtual ~DynamicObj();

protected:
    float moveSpeed;

public:
    virtual HRESULT Initialize() abstract;
    virtual SceneType Update() abstract;
    virtual void Render() abstract;
    virtual void Release() abstract;
    virtual Object* Clone() abstract;

public:
    // 길찾기 시작 기능
    void AStarStart(const D3DXVECTOR3& startPos, const D3DXVECTOR3& destPos);
    // 길찾기를 통해 얻은 경로를 따라 이동하는 기능
    void AStarMove();
};

