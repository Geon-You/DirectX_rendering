#include "SceneMgr.h"
#include "Scene.h"
#include "Title.h"
#include "Ingame.h"

SceneMgr::SceneMgr()
	:currentScene(nullptr)
{
}

SceneMgr::~SceneMgr()
{
	Release();
}

HRESULT SceneMgr::SetScene(SceneType type)
{
	// ���� ���� �����Ѵٸ�, ����
	SafeDelete(currentScene);

	// �� Ÿ�Կ� ���� ���� �� ��ü �Ҵ�
	switch (type)
	{
	case SCENE_TITLE:
		currentScene = new Title;
		break;
	case SCENE_INGAME:
		currentScene = new Ingame;
		break;
	}

	// �� �ʱ�ȭ
	if (FAILED(currentScene->Initialize()))
	{
		ERR_MSG(g_hWnd, L"�� �ʱ�ȭ ����");
		return E_FAIL;
	}

	return S_OK;
}

void SceneMgr::Update()
{
	currentScene->Update();
}

void SceneMgr::Render()
{
	currentScene->Render();
}

void SceneMgr::Release()
{
	SafeDelete(currentScene);
}

