#pragma once
#include "Define.h"
#include "Function.h"

class Device
{
public:
	DECLARE_SINGLETON(Device);

private:
	Device(void);
public:
	~Device(void);

private:
	// ��ġ ���� ���縦 ���� ���̷�Ʈ ��ü
	LPDIRECT3D9	direct;

	// ��ġ�� ��ǥ�ϴ� ��ü
	LPDIRECT3DDEVICE9 device;

	// �̹��� ������ ��ǥ�ϴ� sprite��ügh
	LPD3DXSPRITE	sprite;

	// ��Ʈ
	LPD3DXFONT		font;
	// ����
	LPD3DXLINE      line;

public:
	HRESULT InitDevice(WINMODE mode);
	void RenderBegin();
	void RenderEnd();
	void Release();
public:
	LPDIRECT3DDEVICE9 GetDevice() { return device; }
	LPD3DXSPRITE	  GetSprite() { return sprite; }
	LPD3DXFONT		  GetFont() { return font; }
	LPD3DXLINE	      GetLine() { return line; }
};
