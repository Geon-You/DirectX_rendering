#include "AStar.h"
#include "Include.h"

AStar::AStar()
{
}

AStar::~AStar()
{
}

void AStar::AstarStart(int _startIdx, int _goalIdx)
{
	// 이동할 타일이 시작 타일과 동일한다면 리턴
	if (_startIdx == _goalIdx)
		return;

	// 타일 정보 불러오기
	auto tiles = GET_SINGLE(ObjMgr)->GetTiles();

	// 타일 정보가 없다면 리턴
	if (tiles == nullptr)
		return;

	// 골 인덱스의 타일이 캐릭터가 서 있을 수 없는 (충돌하는) 타일이라면 리턴
	if ((*tiles)[_goalIdx]->isColl == true)
		return;

	// 이미 골이 지정된 상태에서, ASart가 또 호출될 경우
	// 기존에 있던 데이터들을 해제하기 위해 호출
	Release();

	startIdx = _startIdx;
	goalIdx = _goalIdx;

	// 경로 생성 시작
	MakeRoute();
}

void AStar::MakeRoute()
{
	// 시작 노드 생성
	NODE* node = new NODE;
	// 노드의 타일 인덱스를 길찾기 시작한 타일 인덱스로
	node->idx = startIdx;
	// 해당 노드가 시작 노드이므로 부모 없음
	node->parent = NULL;
	node->fCost = 0;

	// 시작 노드를 이미 조사한 대상으로 등록
	closeList.push_back(node);

	// 타일 정보 불러오기
	auto tiles = GET_SINGLE(ObjMgr)->GetTiles();
	if (tiles == nullptr)
		return;

	// 인접 타일 검사 시, 임의로 타일 인덱스를 잠시 담아두기 위한 변수
	int index = 0;

	while (true)
	{
		// 위
		index = node->idx - TILE_CNT_X; // 한 칸 위의 타일 인덱스를 구함

		// 존재하는 타일인지? (올바른 인덱스)
		// 갈 수 있는 타일인지? (충돌 여부)
		// 이미 조사했거나, 조사할 대상에 포함되어 있는 녀석은 제외
		//   -> 클로즈, 오픈 리스트에 이미 존재한다면 제외
		if (index >= 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			// 타일 인덱스에 해당하는 타일 정보(노드)를 생성 후,
			// 오픈 리스트(조사할 대상)에 추가
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 아래
		index = node->idx + TILE_CNT_X;
		if (index < (TILE_CNT_X * TILE_CNT_Y)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 오른쪽 
		index = node->idx + 1;
		if (index < (TILE_CNT_X * TILE_CNT_Y) && index % TILE_CNT_X != 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 왼쪽 
		index = node->idx - 1;
		if (index >= 0 && (index % TILE_CNT_X != TILE_CNT_X - 1)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 왼쪽위

		// 오른쪽 위

		// 왼쪽 아래

		// 오른쪽 아래

		// 오픈 리스트를 정렬
		//  -> 비용(거리)를 기준으로 오름차순 정렬
		openList.sort(Compare);

		// 오픈 리스트가 비어있다면 리턴
		if (openList.empty())
			return;

		// 오픈 리스트에서 코스트가 가장 낮은 값을 클로즈리스트에 담음
		auto iter = openList.begin();
		node = *iter;

		closeList.push_back(*iter);
		openList.erase(iter);

		// 검사 중인 노드의 타일 인덱스가 골 인덱스와 같다면
		if (node->idx == goalIdx)
		{
			// 골 인덱스에 도달했다는 것은 경로를 찾았다는 것
			// 따라서, 최적의 경로 데이터를 얻는다.
			while (true)
			{
				// 검사 노드에 접근하여 역순(부모를 통해 접근)으로 타일 인덱스를 얻음
				bestList.push_back(node->idx);
				node = node->parent;
				if (node->idx == startIdx)
					break;
			}
			bestList.reverse();

			break;
		}
	}
}

bool AStar::CheckList(int idx)
{
	// 오픈 or 클로즈 목록에 존재한다면 false,
	// 아니라면 true

	for (auto iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if ((*iter)->idx == idx)
			return false;
	}

	for (auto iter = closeList.begin(); iter != closeList.end(); ++iter)
	{
		if ((*iter)->idx == idx)
			return false;
	}

	return true;
}

NODE* AStar::MakeNode(int idx, NODE* parent, const vector<TILE*>* tiles)
{
	NODE* node = new NODE;
	node->idx = idx;
	node->parent = parent;

	// 부모 노드까지의 거리
	float distanceX = (*tiles)[parent->idx]->posX - (*tiles)[idx]->posX;
	float distanceY = (*tiles)[parent->idx]->posY - (*tiles)[idx]->posY;

	float gCost = sqrt(distanceX * distanceX + distanceY * distanceY);

	// 도착 노드까지의 거리
	float goalDistanceX = (*tiles)[goalIdx]->posX - (*tiles)[idx]->posX;
	float goalDistanceY = (*tiles)[goalIdx]->posY - (*tiles)[idx]->posY;

	float hCost = sqrt(goalDistanceX * goalDistanceX + goalDistanceY * goalDistanceY);

	node->fCost = gCost + hCost;

	return node;
}

void AStar::Release()
{
	// 오픈리스트 비우기
	for (auto iter = openList.begin(); iter != openList.end(); ++iter)
		SafeDelete(*iter);
	openList.clear();

	// 클로즈리스트 비우기
	for (auto iter = closeList.begin(); iter != closeList.end(); ++iter)
		SafeDelete(*iter);
	closeList.clear();

	// 최적 경로 비우기
	bestList.clear();
}
