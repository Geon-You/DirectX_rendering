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
    // DynamicObj을(를) 통해 상속됨
    HRESULT Initialize() override;
    SceneType Update() override;
    void Render() override;
    void Release() override;
    Object* Clone() override;
};

