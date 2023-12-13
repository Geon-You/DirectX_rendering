#pragma once
#include "Texture.h"
class MultiTexture :
	public Texture
{
public:
	MultiTexture();
	virtual ~MultiTexture();

private:
	// ������ ���� ���� �ؽ��ĸ� ���� ��
	// ex) ������ �ִϸ��̼��� ��� �� �� ������ ���� �и��Ǿ��� ���
	// key - ������ ���, value - ������ ��� ������ 1~5
	// key - ������ ����, value - ������ ���� ������ 1~7
	map<const TCHAR*, vector<TEXINFO*>> texMap; 

public:
	// Texture��(��) ���� ��ӵ�
	virtual const TEXINFO* GetTexture(const TCHAR* key = nullptr, const int& cnt = 0) override;
	virtual HRESULT InsertTexture(const TCHAR* path, const TCHAR* key = nullptr, const int& cnt = 0) override;
	virtual void Release() override;
};

