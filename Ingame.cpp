#include "Ingame.h"
#include "Include.h"

HRESULT Ingame::Initialize()
{
	// 씬이 초기화 될 때, 타임매니저 초기화
	GET_SINGLE(TimeMgr)->Initialize();

	// 원형객체를 생성을 위한 해당 씬의 프로토타입 객체를 생성해둔다.
	proto = new IngameObjProto;
	// 해당 씬의 원형 객체 생성
	if (FAILED(proto->Initialize()))
	{
		ERR_MSG(g_hWnd, L"원형 객체 생성 실패");
		return E_FAIL;
	}

	// 파라미터의 넘긴 키 값의 원형객체를 찾아, 객체를 복제 후 ObjMgr에 등록
	GET_SINGLE(ObjMgr)->AddObject(proto, L"TileBG");
	GET_SINGLE(ObjMgr)->AddObject(proto, L"Player");
	GET_SINGLE(ObjMgr)->AddObject(proto, L"PlayerEffect");

	// 해당 씬에서 사용할 각종 텍스처 로드
	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Tile.png",
		L"TileBG", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"TileBG 텍스처 추가 실패");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_DOWN.png",
		L"Player_DOWN", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_DOWN 텍스처 추가 실패");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_UP.png",
		L"Player_UP", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_UP 텍스처 추가 실패");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_LEFT.png",
		L"Player_LEFT", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_LEFT 텍스처 추가 실패");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Player/Player_RIGHT.png",
		L"Player_RIGHT", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"Player_RIGHT 텍스처 추가 실패");
		return E_FAIL;
	}

	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Ingame/Effect/PlayerEffect_%d.png",
		L"PlayerEffect", TEX_MULTI, L"Fire", 39)))
	{
		ERR_MSG(g_hWnd, L"PlayerEffect 텍스처 추가 실패");
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
