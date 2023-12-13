#include "ObjMgr.h"
#include "Object.h"
#include "Prototype.h"
#include "Include.h"

ObjMgr::ObjMgr()
{
}

ObjMgr::~ObjMgr()
{
	this->Release();
}

SceneType ObjMgr::Update()
{
	for (auto iter = objs.begin(); iter != objs.end(); ++iter)
	{
		for (auto sIter = iter->second.begin(); sIter != iter->second.end(); ++sIter)
		{
			SceneType t = (*sIter)->Update();
			if (t > SCENE_NONE)
				return t;

			GET_SINGLE(SortMgr)->AddObject(*sIter);
		}
	}

	return SCENE_NONE;
}

void ObjMgr::Render()
{
	GET_SINGLE(SortMgr)->RenderObject();
}

void ObjMgr::Release()
{
	for (auto iter = objs.begin(); iter != objs.end(); ++iter)
	{
		for (auto sIter = iter->second.begin(); sIter != iter->second.end(); ++sIter)
		{
			SafeDelete(*sIter);
		}
		iter->second.clear();
	}
	objs.clear();
	SortMgr::Destroy();
}

const vector<TILE*>* ObjMgr::GetTiles()
{
	auto iter = objs.find(L"TileBG");

	if (iter == objs.end())
	{
		ERR_MSG(g_hWnd, L"TileBG ��ü�� �����ϴ�.");
		return nullptr;
	}

	return ((TileBackGround*)(iter->second.front()))->GetTiles();
}

const D3DXVECTOR3* ObjMgr::GetScroll()
{
	auto iter = objs.find(L"TileBG");

	if (iter == objs.end())
	{
		ERR_MSG(g_hWnd, L"TileBG ��ü�� �����ϴ�.");
		return nullptr;
	}

	return ((TileBackGround*)(iter->second.front()))->GetScroll();
}

const D3DXVECTOR3 ObjMgr::GetScrollMousePos()
{
	auto mousePos = Mouse::GetPos();
	auto scroll = GET_SINGLE(ObjMgr)->GetScroll();

	return D3DXVECTOR3((float)mousePos.x - scroll->x, (float)mousePos.y - scroll->y, 0);
}

const INFO* ObjMgr::GetInfo(const TCHAR* key, const int& cnt)
{
	auto iter = objs.find(key);

	if (iter == objs.end())
		return nullptr;

	auto sIter = iter->second.begin();
	for (int i = 0; i < cnt; ++i)
		++sIter;

	return (*sIter)->GetInfo();
}

Object* ObjMgr::AddObject(Prototype* proto, const TCHAR* key)
{
	// �ʿ��� �ߺ��� Ű���� ���� ��ü�� �ִ��� ����
	auto iter = objs.find((TCHAR*)key);

	// �ʿ� ����Ǿ��ִ� ������ü�� ������
	Object* protoInstance = ((ObjProto*)proto)->GetProto(key);

	// �ش� ������ü�� ���� ��ü�� �����ؼ� ����
	Object* clone = protoInstance->Clone();
	clone->Initialize();

	// iter�� end�� ���ٸ� �ش� Ű���� ����.
	if (iter == objs.end())
	{
		list<Object*> objList;
		objList.push_back(clone);

		objs.insert(make_pair(key, objList));
	}
	else
	{
		// Ű���� �̹� �����Ѵٸ�, �ش� ��ü ����Ʈ�� �߰��Ѵ�.
		iter->second.push_back(clone);
	}

	return clone;
}


