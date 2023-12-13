#pragma once
#include "Include.h"

class AStar
{
private:
	static AStar* instance;

public:
	DECLARE_SINGLETON(AStar);

private:
	AStar();
public:
	~AStar();

private:
	list<NODE*> openList;  // 조사해야할 대상들
	list<NODE*> closeList; // 이미 조사한 대상들
	list<int> bestList;    // 조사한 최적의 경로인 타일들의 인덱스

public:
	int startIdx; // 길찾기를 시작할 타일의 인덱스 (현재 캐릭터가 있는 타일)
	int goalIdx;  // 목표 타일의 인덱스 (마우스로 클릭한 타일)

public:
	// 길찾기 시작 시, 호출할 함수
	void AstarStart(int _startIdx, int _goalIdx);
	// 최적 경로를 생성하는 함수
	void MakeRoute();
	// 파라미터로 특정 타일의 인덱스를 받아, 해당 타일이
	// 오픈 or 클로즈 리스트에 이미 존재하는지 확인하는 함수
	bool CheckList(int idx);
	// 노드 데이터 생성을 위한 함수
	NODE* MakeNode(int idx, NODE* parent, const vector<TILE*>* tiles);
	void Release();
	// 최적 경로를 갖는 목록의 주소를 반환
	list<int>* GetBestList() { return &bestList; }

public:
	static bool Compare(NODE* a, NODE* b)
	{
		return a->fCost < b->fCost;
	}
};

