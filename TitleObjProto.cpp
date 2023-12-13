#include "TitleObjProto.h"
#include "Include.h"

HRESULT TitleObjProto::Initialize()
{
	INFO info;
	ZeroMemory(&info, sizeof(info));

	D3DXMatrixIdentity(&info.world); // ������ķ� ������ִ� �Լ�
	info.pos = D3DXVECTOR3(WIN_SIZE_X / 2.f, WIN_SIZE_Y / 2.f, 0.f);
	info.dir = D3DXVECTOR3(0.f, 0.f, 0.f);
	info.look = D3DXVECTOR3(1.f, 0.f, 0.f);

	protoObjs.insert(make_pair(L"TitleBG", new BackGround(info)));

    return S_OK;
}

TitleObjProto::TitleObjProto()
{
}

TitleObjProto::~TitleObjProto()
{
}
