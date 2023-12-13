#include "Player.h"
#include "Include.h"

Player::Player()
{
}

Player::Player(const INFO& info)
    :DynamicObj(info)
{
}

Player::~Player()
{
    Release();
}

HRESULT Player::Initialize()
{
    isClicked = false;
    sortOrder = SORT_SECOND;
    objKey = (TCHAR*)L"Player";
    stateKey = (TCHAR*)L"Player_DOWN";
    frame = FRAME(0, 0, 3, 0.01f);

    info.pos = GetTilePos(125);
    info.size = D3DXVECTOR3(200.f, 200.f, 0);
    moveSpeed = 0.2f;

    return S_OK;
}

SceneType Player::Update()
{
    // 모션 갱신
    UpdateMotion();
    // 프레임 갱신
    UpdateFrame();

    if (GET_SINGLE(KeyMgr)->GetKey() & KEY_LM && !isClicked)
    {
        isClicked = true;
        AStarStart(info.pos, GET_SINGLE(ObjMgr)->GetScrollMousePos());
    }
    
    if ((GET_SINGLE(KeyMgr)->GetKey() & KEY_LM) == false)
        isClicked = false;

    AStarMove();

    auto scroll = GET_SINGLE(ObjMgr)->GetScroll();

    D3DXMatrixTranslation(&info.world
        , info.pos.x + scroll->x
        , info.pos.y + scroll->y
        , info.pos.z);

    return SCENE_NONE;
}

void Player::Render()
{
    // 현재 플레이어가 방향 별로 다른 이미지를 사용하므로,
    // stateKey <- 멀티텍스처 용도이나, 해당 값을 임시로 drawKey 처럼 사용
    auto texInfo = GET_SINGLE(TextureMgr)->GetTexture(stateKey);
    if (texInfo == NULL)
        return;

    info.center = D3DXVECTOR3(info.size.x * .5f, info.size.y * .5f, 0.f);

    RECT rc = { info.size.x * (int)frame.current,
        info.size.y * (int)frame.animType,
        info.size.x * (int)frame.current + info.size.x ,
        info.size.y * (int)frame.animType + info.size.y };

    GET_SINGLE(Device)->GetSprite()->SetTransform(&info.world);
    GET_SINGLE(Device)->GetSprite()->Draw(texInfo->texture, &rc
        , &info.center, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Player::Release()
{
}

Object* Player::Clone()
{
    return new Player(*this);
}

void Player::UpdateMotion()
{
    if (info.dir.x == 0 && info.dir.y == 0)
    {
        frame.animType = 0;
        frame.last = 3;
        return;
    }
    else
    {
        frame.animType = 1;
        frame.last = 5;
    }

    bool isHorizontal = abs(info.dir.x) > abs(info.dir.y);

    if (isHorizontal)
    {
        if (info.dir.x < 0)
        {
            stateKey = (TCHAR*)L"Player_LEFT";
        }
        else if (info.dir.x > 0)
        {
            stateKey = (TCHAR*)L"Player_RIGHT";
        }
    }
    else
    {
        if (info.dir.y < 0)
        {
            stateKey = (TCHAR*)L"Player_UP";
        }
        else if (info.dir.y > 0)
        {
            stateKey = (TCHAR*)L"Player_DOWN";
        }
    }
}