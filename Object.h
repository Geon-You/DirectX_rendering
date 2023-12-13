#pragma once
#include "Define.h"
#include "Function.h"

class Object abstract
{
protected:
	INFO info;
	TCHAR* objKey;			// ��ü�� Ű �� (�ؽ�ó Ű ���� �����ϰ� ����ϰ� ����)
	TCHAR* stateKey;		// ����� Ű �� (��Ƽ �ؽ�ó�� ���)	
	SortOrder sortOrder;	// �׸��� ����
	FRAME frame;

public:
	virtual void SetRenderInfo(const TCHAR* objKey, SortOrder sortOrder = SORT_FIRST, const TCHAR* stateKey = NULL)
	{
		this->objKey = (TCHAR*)objKey;
		this->stateKey = (TCHAR*)stateKey;
		this->sortOrder = sortOrder;
	}

public:
	virtual HRESULT Initialize() abstract;
	virtual SceneType Update() abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;
	virtual Object* Clone() abstract;

public:
	const INFO* GetInfo() { return &info; }
	SortOrder GetSortOrder() { return sortOrder; }
	// ���� ������ ���� ���
	void UpdateFrame();
	// �Ķ���ͷ� ���� ��ġ�� �ش��ϴ� Ÿ���� �ε����� ��ȯ
	int GetTileIndex(const D3DXVECTOR3& pos);
	// �Ķ���ͷ� ���� Ÿ�� �ε����� �ش��ϴ� Ÿ�� ��ġ ��ȯ
	const D3DXVECTOR3 GetTilePos(int idx);
	// Ư�� ����Ʈ�� Ư�� Ÿ���� �浹�ϴ��� Ȯ���ϴ� ���
	bool CollPosToTile(const D3DXVECTOR3& pos, const TILE* tileInfo);
	

public:
	Object();
	Object(const INFO& info);
	virtual ~Object();
};

