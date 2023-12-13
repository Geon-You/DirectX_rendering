#include "Title.h"
#include "Include.h"

HRESULT Title::Initialize()
{
	// ���� �ʱ�ȭ �� ��, Ÿ�ӸŴ��� �ʱ�ȭ
	GET_SINGLE(TimeMgr)->Initialize();

	// ������ü�� ������ ���� �ش� ���� ������Ÿ�� ��ü�� �����صд�.
	proto = new TitleObjProto;
	// �ش� ���� ���� ��ü ����
	if (FAILED(proto->Initialize()))
	{
		ERR_MSG(g_hWnd, L"���� ��ü ���� ����");
		return E_FAIL;
	}

	// �Ķ������ �ѱ� Ű ���� ������ü�� ã��, ��ü�� ���� �� ObjMgr�� ���
	GET_SINGLE(ObjMgr)->AddObject(proto, L"TitleBG")->SetRenderInfo(L"TitleBG");

	// �ش� ������ ����� ���� �ؽ�ó �ε�
	if (FAILED(GET_SINGLE(TextureMgr)->InsertTexture(L"Texture/Title/TitleBG.png",
		L"TitleBG", TEX_SINGLE)))
	{
		ERR_MSG(g_hWnd, L"TitleBG �ؽ�ó �߰� ����");
		return E_FAIL;
	}


	return S_OK;
}

void Title::Update()
{
	// ��ŸŸ�� ����
	GET_SINGLE(TimeMgr)->Update();
	// ������Ʈ �Ŵ����� ���� ���� ���� ��� ��ü�� �����Ѵ�.
	// �� ��, ��ü ������Ʈ �Լ��� ��ȯ ������ SceneType�� �޾�
	// ���Ѵٸ� Ư�� ��ü�� ���� ����, �ٸ� ������ ��ȯ�� �� �ְԲ� ��������
	SceneType t = GET_SINGLE(ObjMgr)->Update();

	if (GET_SINGLE(KeyMgr)->GetKey() & KEY_SPACE)
		t = SCENE_INGAME;

	if (t != SCENE_NONE)
	{
		GET_SINGLE(SceneMgr)->SetScene(t);
		return;
	}
}

void Title::Render()
{
	GET_SINGLE(ObjMgr)->Render();
}

void Title::Release()
{
	GET_SINGLE(ObjMgr)->Destroy();
	GET_SINGLE(TextureMgr)->Destroy();
	GET_SINGLE(TimeMgr)->Destroy();
	SafeDelete(proto);
}

Title::Title()
{
}

Title::~Title()
{
	Release();
}
