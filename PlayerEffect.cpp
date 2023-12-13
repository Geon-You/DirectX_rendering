#include "PlayerEffect.h"
#include "Include.h"

PlayerEffect::PlayerEffect()
{
}

PlayerEffect::PlayerEffect(const INFO& info)
    : DynamicObj(info)
{
}

PlayerEffect::~PlayerEffect()
{
    Release();
}

HRESULT PlayerEffect::Initialize()
{
    sortOrder = SORT_THIRD;
    objKey = (TCHAR*)L"PlayerEffect";
    stateKey = (TCHAR*)L"Fire";
    frame = FRAME(0, 0, 38, 0.01f);

    info.pos = D3DXVECTOR3(4.f,-60.f, 0);

    return S_OK;
}

SceneType PlayerEffect::Update()
{
    UpdateFrame();

    D3DXMATRIX matTrans, matScale;

    // �÷��̾ ����ٴ� ����Ʈ�̹Ƿ�, �÷��̾� ������ ������
    auto playerInfo = GET_SINGLE(ObjMgr)->GetInfo(L"Player");
    
    D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, info.pos.z);
    D3DXMatrixScaling(&matScale, .25f, 1.f, 1.f);

    // ����Ʈ ���� =  ����Ʈ ������ * ����Ʈ ���� ��ġ * �÷��̾� ���� (���� �� �÷��̾ ����Ʈ�� �θ� ��) 
    info.world = matScale * matTrans * playerInfo->world;

    return SCENE_NONE;
}

void PlayerEffect::Render()
{
    // ���� ���¸� �����Ͽ� �پ��� ȿ���� �� �� ����
    // ������ ���� ���� ���� ��, ������ �̹� ��ο�� ��������Ʈ�鵵 ���� ������ ����
    // Draw �� ȣ�� ���� �׷����°� �ƴ϶�, ��Ƽ� �״ٰ� �ѹ��� ����ϱ� ������
    // ������ �̹� �׷��� ��ü���� ������ ���� �ʰ� Flush()�� ����,
    // ������ Draw�� ��������Ʈ���� ��ġ�� ���� ������.
    GET_SINGLE(Device)->GetSprite()->Flush();

    // src : �׸����� �ϴ� �̹����� �÷�
    // dest : �̹� �׷��� �̹����� �÷�
    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE); // (src * 1(����))
    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); // (dest * 1(����))
    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); // � ������ �� ������ (result = src * 1 + dest * 1)

    const TEXINFO* texInfo = GET_SINGLE(TextureMgr)->GetTexture(objKey, stateKey, (int)frame.current);
    if (texInfo == nullptr)
        return;

    info.center = D3DXVECTOR3(texInfo->ImgInfo.Width / 2.f, texInfo->ImgInfo.Height / 2.f, 0.f);

    GET_SINGLE(Device)->GetSprite()->SetTransform(&info.world);
    GET_SINGLE(Device)->GetSprite()->Draw(texInfo->texture, NULL, &info.center, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void PlayerEffect::Release()
{
}

Object* PlayerEffect::Clone()
{
    return new PlayerEffect(*this);
}
