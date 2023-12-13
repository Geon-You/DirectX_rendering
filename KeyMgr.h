#pragma once
#include "Define.h"
#include "Function.h"

class KeyMgr
{
private:
	// ���� ���� Ű ������ ���� ����
	DWORD dwKey;

public:
	DWORD GetKey() { return dwKey; }

public:
	void CheckKey();

public:
	DECLARE_SINGLETON(KeyMgr);

private:
	KeyMgr();

public:
	~KeyMgr();
};

