#pragma once
#include "Define.h"
#include "Function.h"

class Scene;
class SceneMgr
{
private:
	// ���� �� ��ü�� ���� �ʵ�
	Scene* currentScene; 

public:
	DECLARE_SINGLETON(SceneMgr);
	Scene* GetScene() { return currentScene; }

public:
	// �Ķ���ͷ� ���� �� Ÿ������ ���� ���� �����ϴ� ���
	HRESULT SetScene(SceneType type);
	void Update(); // ���� �� ������Ʈ
	void Render(); // ���� �� �׸���
	void Release();

private:
	SceneMgr();

public:
	~SceneMgr();
};

