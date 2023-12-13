#pragma once
#include "StaticObj.h"

class BackGround :
    public StaticObj
{
public:
    BackGround();
    BackGround(const INFO& info);
    virtual ~BackGround();

public:
    // StaticObj��(��) ���� ��ӵ�
    HRESULT Initialize() override;
    SceneType Update() override;
    void Render() override;
    void Release() override;
    Object* Clone() override;
};

