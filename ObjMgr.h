#pragma once
#include "Define.h"
#include "Function.h"

class Object;
class Prototype;
class ObjMgr
{
public:
	DECLARE_SINGLETON(ObjMgr);

private:
	ObjMgr();
public:
	~ObjMgr();

private:
	map<const TCHAR*, list<Object*>>	objs;

public:
	const vector<TILE*>* GetTiles();
	const D3DXVECTOR3* GetScroll();
	const D3DXVECTOR3 GetScrollMousePos();
	const INFO* GetInfo(const TCHAR* key, const int& cnt = 0);

public:
	Object* AddObject(Prototype* proto, const TCHAR* key);
	SceneType Update();
	void Render();
	void Release();
};

