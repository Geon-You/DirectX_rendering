#include "Ingame.h"
#include "Include.h"

HRESULT Ingame::Initialize()
{
	// ���� �ʱ�ȭ �� ��, Ÿ�ӸŴ��� �ʱ�ȭ
	GET_SINGLE(TimeMgr)->Initialize();

	// ������ü�� ������ ���� �ش� ���� ������Ÿ�� ��ü�� �����صд�.
	proto = new IngameObjProto;
	// �ش� ���� ���� ��ü ����
	if (FAILED(proto->Initialize()))
	{
		ERR_MSG(g_hWnd, L"���� ��ü ���� ����");
		return E_FAIL;
	}

	// �Ķ������ �ѱ� Ű ���� ������ü�� ã��, ��ü�� ���� �� ObjMgr�� ���
	GET_SINGLE(ObjMgr)->AddObject(proto, L"TileBG");
	GET_SINGLE(ObjMgr)->AddObject(proto, L"Player");
	GET_SINGLE(ObjMgr)->AddObject(proto, L"PlayerEffect");

	// �ش� ������ ����� ���� �ؽ�ó �ε�
	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Tile.png",
		L"TileBG", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"TileBG �ؽ�ó �߰� ����");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_DOWN.png",
		L"Player_DOWN", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_DOWN �ؽ�ó �߰� ����");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_UP.png",
		L"Player_UP", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_UP �ؽ�ó �߰� ����");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_LEFT.png",
		L"Player_LEFT", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_LEFT �ؽ�ó �߰� ����");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_RIGHT.png",
		L"Player_RIGHT", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_RIGHT �ؽ�ó �߰� ����");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Effect/PlayerEffect_%d.png",
		L"PlayerEffect", TEX_MULTI, L"Fire", 39)))
	{
		ERR_MSG(g_hWnd, L"PlayerEffect �ؽ�ó �߰� ����");
		return E_FAIL;
	}

    return S_OK;
}

void Ingame::Update()
{
	GET_SINGLE(TimeMgr)->Update();
	SceneType t = GET_SINGLE(ObjMgr)->Update();

	if (t != SCENE_NONE)
	{
		GET_SINGLE(SceneMgr)->SetScene(t);
		return;
	}
}

void Ingame::Render()
{
	GET_SINGLE(ObjMgr)->Render();
}

void Ingame::Release()
{
	GET_SINGLE(ObjMgr)->Destroy();
	GET_SINGLE(TextureMgr)->Destroy();
	GET_SINGLE(TimeMgr)->Destroy();
	SafeDelete(proto);
}

Ingame::Ingame()
{
}

Ingame::~Ingame()
{
    Release();
}
