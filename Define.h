#pragma once
#include "framework.h"

const int WIN_SIZE_X = 800;
const int WIN_SIZE_Y = 600;

extern HWND g_hWnd;

// 윈도우 모드
enum WINMODE
{
	WINMODE_FULL,	// 풀스크린
	WINMODE_WIN,	// 창모드
};

// 텍스처 타입을 열거
enum TexType
{
	TEX_SINGLE,
	TEX_MULTI,
};

// 씬 종류를 열거
enum SceneType
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_INGAME,
	SCENE_END,
};

// 객체 종류를 열거
enum ObjType
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_END,
};

// 그리기 순서를 나타내는 열거형
enum SortOrder
{
	SORT_FIRST,
	SORT_SECOND,
	SORT_THIRD,
	SORT_END,
};

// 텍스쳐 객체와 이미지 원본 정보를 갖는 구조체
typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9	texture;	// 텍스쳐
	D3DXIMAGE_INFO		ImgInfo;	// 이미지(원본)의 정보
}TEXINFO;

// 모든 액터가 공통으로 갖는 데이터를 모아놓은 구조체
typedef struct tagInfo
{
	D3DXVECTOR3 pos;	 // 위치 (로컬 좌표)
	D3DXVECTOR3 dir;	 // 방향 벡터
	D3DXVECTOR3 look;	 // 바라보는 벡터 (초기 방향을 나타내는 단위 벡터)
	D3DXVECTOR3 size;
	D3DXVECTOR3	center;  // 로컬기준 중심점의 좌표
	D3DXMATRIX	world;   // 월드 행렬

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

// 애니메이션 처리에 사용되는 데이터를 모아놓은 구조체
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

// cnt x * cnt y 로 맵의 크기가 결정됨
const int TILE_CNT_X = 30;
const int TILE_CNT_Y = 30;

// 하나의 타일 기본 사이즈
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

// astar 알고리즘 
// -> 대표적인 휴리스틱 알고리즘
// 

typedef struct AstarNode
{
					   // F = G + H 
	float	fCost;     // 비용 = 부모 노드까지의 거리 + 도착 노드까지의 거리
	int		idx;       // 타일 인덱스	
	AstarNode* parent; // 시작점이 되는 노드
}NODE;

// 게임 내 사용될 키들을 아래에 별도의 상수로 정의
const DWORD KEY_UP		= 0b00000001;
const DWORD KEY_DOWN	= 0b00000010;
const DWORD KEY_LEFT	= 0b00000100;
const DWORD KEY_RIGHT	= 0b00001000;
const DWORD KEY_SPACE	= 0b00010000;
const DWORD KEY_LM		= 0b00100000;
const DWORD KEY_1		= 0b01000000;

// 플레이어 상태 정의
const DWORD STATE_IDLE	= 0b00000001;
const DWORD STATE_WALK	= 0b00000010;
const DWORD STATE_ATK	= 0b00000100;
const DWORD STATE_HIT	= 0b00001000; 
const DWORD STATE_DEAD	= 0b00010000;