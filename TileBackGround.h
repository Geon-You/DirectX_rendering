#pragma once
#include "StaticObj.h"

class TileBackGround :
    public StaticObj
{
public:
    TileBackGround();
    TileBackGround(const INFO& info);
    virtual ~TileBackGround();
private:
    bool isDrawTileIndex;
    vector<TILE*> tiles;
    D3DXVECTOR3 scroll;

public:
    vector<TILE*>* GetTiles() { return &tiles; }
    const D3DXVECTOR3* GetScroll() { return &scroll; }

private:
    void LoadTileFromFile();
    void UpdateScroll();
    void DrawTileIndex(int index);

public:
    HRESULT Initialize() override;
    SceneType Update() override;
    void Render() override;
    void Release() override;
    Object* Clone() override;
};

