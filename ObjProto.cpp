#include "ObjProto.h"

ObjProto::ObjProto(void)
{
}

ObjProto::~ObjProto(void)
{
	this->Release();
}

void ObjProto::Release()
{
	for (auto iter = protoObjs.begin();
		iter != protoObjs.end(); ++iter)
	{
		SafeDelete((iter->second));
	}
	protoObjs.clear();
}

Object* ObjProto::GetProto(const TCHAR* key)
{
	auto iter = protoObjs.find(key);

	if (iter == protoObjs.end())
	{
		ERR_MSG(g_hWnd, L"�����Ϸ��� ������ü�� �����ϴ�.");
		return nullptr;
	}

	return iter->second;
}
