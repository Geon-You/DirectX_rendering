#pragma once
#include "Texture.h"
class SingleTexture :
	public Texture
{
public:
	SingleTexture();
	virtual ~SingleTexture();

private:
	TEXINFO* texInfo; // �ؽ�ó ������ ���� �ʵ�

public:
	// Texture��(��) ���� ��ӵ�
	virtual const TEXINFO* GetTexture(const TCHAR* key = nullptr, const int& cnt = 0) override;
	virtual HRESULT InsertTexture(const TCHAR* path, const TCHAR* key = nullptr, const int& cnt = 0) override;
	virtual void Release() override;
};

