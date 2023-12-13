#pragma once
#include "DynamicObj.h"
class Player :
    public DynamicObj
{
public:
    Player();
    Player(const INFO& info);
    virtual ~Player();

private:
    bool isClicked;

private:
    void UpdateMotion();

public:
    // DynamicObj��(��) ���� ��ӵ�
    HRESULT Initialize() override;
    SceneType Update() override;
    void Render() override;
    void Release() override;
    Object* Clone() override;
};

