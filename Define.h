#pragma once
#include "framework.h"

const int WIN_SIZE_X = 800;
const int WIN_SIZE_Y = 600;

extern HWND g_hWnd;

// ������ ���
enum WINMODE
{
	WINMODE_FULL,	// Ǯ��ũ��
	WINMODE_WIN,	// â���
};

// �ؽ�ó Ÿ���� ����
enum TexType
{
	TEX_SINGLE,
	TEX_MULTI,
};

// �� ������ ����
enum SceneType
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_INGAME,
	SCENE_END,
};

// ��ü ������ ����
enum ObjType
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_END,
};

// �׸��� ������ ��Ÿ���� ������
enum SortOrder
{
	SORT_FIRST,
	SORT_SECOND,
	SORT_THIRD,
	SORT_END,
};

// �ؽ��� ��ü�� �̹��� ���� ������ ���� ����ü
typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9	texture;	// �ؽ���
	D3DXIMAGE_INFO		ImgInfo;	// �̹���(����)�� ����
}TEXINFO;

// ��� ���Ͱ� �������� ���� �����͸� ��Ƴ��� ����ü
typedef struct tagInfo
{
	D3DXVECTOR3 pos;	 // ��ġ (���� ��ǥ)
	D3DXVECTOR3 dir;	 // ���� ����
	D3DXVECTOR3 look;	 // �ٶ󺸴� ���� (�ʱ� ������ ��Ÿ���� ���� ����)
	D3DXVECTOR3 size;
	D3DXVECTOR3	center;  // ���ñ��� �߽����� ��ǥ
	D3DXMATRIX	world;   // ���� ���

	tagInfo() {}
	tagInfo(const tagInfo& Info)
		:pos(Info.pos)
		, dir(Info.dir)
		, look(Info.look)
		, size(Info.size)
		, center(Info.center)
		, world(Info.world)
	{}
}INFO;

// �ִϸ��̼� ó���� ���Ǵ� �����͸� ��Ƴ��� ����ü
typedef struct tagFrame
{
	int animType; 
	float current; 
	float last;
	float time;

	tagFrame() {}
	tagFrame(int _animType, float _current, float _last, float _time)
		: animType(_animType), current(_current), last(_last), time(_time) {}
}FRAME;

// cnt x * cnt y �� ���� ũ�Ⱑ ������
const int TILE_CNT_X = 30;
const int TILE_CNT_Y = 30;

// �ϳ��� Ÿ�� �⺻ ������
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

typedef struct tagTile
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	int drawId;
	bool isColl;
}TILE;

// astar �˰��� 
// -> ��ǥ���� �޸���ƽ �˰���
// 

typedef struct AstarNode
{
					   // F = G + H 
	float	fCost;     // ��� = �θ� �������� �Ÿ� + ���� �������� �Ÿ�
	int		idx;       // Ÿ�� �ε���	
	AstarNode* parent; // �������� �Ǵ� ���
}NODE;

// ���� �� ���� Ű���� �Ʒ��� ������ ����� ����
const DWORD KEY_UP		= 0b00000001;
const DWORD KEY_DOWN	= 0b00000010;
const DWORD KEY_LEFT	= 0b00000100;
const DWORD KEY_RIGHT	= 0b00001000;
const DWORD KEY_SPACE	= 0b00010000;
const DWORD KEY_LM		= 0b00100000;
const DWORD KEY_1		= 0b01000000;

// �÷��̾� ���� ����
const DWORD STATE_IDLE	= 0b00000001;
const DWORD STATE_WALK	= 0b00000010;
const DWORD STATE_ATK	= 0b00000100;
const DWORD STATE_HIT	= 0b00001000; 
const DWORD STATE_DEAD	= 0b00010000;