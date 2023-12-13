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

    // 플레이어를 따라다닐 이펙트이므로, 플레이어 정보를 가져옴
    auto playerInfo = GET_SINGLE(ObjMgr)->GetInfo(L"Player");
    
    D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, info.pos.z);
    D3DXMatrixScaling(&matScale, .25f, 1.f, 1.f);

    // 이펙트 월드 =  이펙트 스케일 * 이펙트 로컬 위치 * 플레이어 월드 (계층 상 플레이어가 이펙트의 부모가 됨) 
    info.world = matScale * matTrans * playerInfo->world;

    return SCENE_NONE;
}

void PlayerEffect::Render()
{
    // 렌더 상태를 변경하여 다양한 효과를 줄 수 있음
    // 하지만 렌더 상태 변경 시, 기존에 이미 드로우된 스프라이트들도 같이 영향을 받음
    // Draw 가 호출 순간 그려지는게 아니라, 모아서 뒀다가 한번에 출력하기 때문에
    // 기존에 이미 그려진 객체들이 영향을 받지 않게 Flush()를 통해,
    // 기존에 Draw한 스프라이트들을 장치로 전부 제출함.
    GET_SINGLE(Device)->GetSprite()->Flush();

    // src : 그리고자 하는 이미지의 컬러
    // dest : 이미 그려진 이미지의 컬러
    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE); // (src * 1(알파))
    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); // (dest * 1(알파))
    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); // 어떤 연산을 할 것인지 (result = src * 1 + dest * 1)

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
