#pragma once
#include "DynamicObj.h"
class PlayerEffect :
    public DynamicObj
{
public:
    PlayerEffect();
    PlayerEffect(const INFO& info);
    virtual ~PlayerEffect();

public:
    // DynamicObj��(��) ���� ��ӵ�
    HRESULT Initialize() override;
    SceneType Update() override;
    void Render() override;
    void Release() override;
    Object* Clone() override;
};

