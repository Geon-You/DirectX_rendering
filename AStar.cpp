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
	// �̵��� Ÿ���� ���� Ÿ�ϰ� �����Ѵٸ� ����
	if (_startIdx == _goalIdx)
		return;

	// Ÿ�� ���� �ҷ�����
	auto tiles = GET_SINGLE(ObjMgr)->GetTiles();

	// Ÿ�� ������ ���ٸ� ����
	if (tiles == nullptr)
		return;

	// �� �ε����� Ÿ���� ĳ���Ͱ� �� ���� �� ���� (�浹�ϴ�) Ÿ���̶�� ����
	if ((*tiles)[_goalIdx]->isColl == true)
		return;

	// �̹� ���� ������ ���¿���, ASart�� �� ȣ��� ���
	// ������ �ִ� �����͵��� �����ϱ� ���� ȣ��
	Release();

	startIdx = _startIdx;
	goalIdx = _goalIdx;

	// ��� ���� ����
	MakeRoute();
}

void AStar::MakeRoute()
{
	// ���� ��� ����
	NODE* node = new NODE;
	// ����� Ÿ�� �ε����� ��ã�� ������ Ÿ�� �ε�����
	node->idx = startIdx;
	// �ش� ��尡 ���� ����̹Ƿ� �θ� ����
	node->parent = NULL;
	node->fCost = 0;

	// ���� ��带 �̹� ������ ������� ���
	closeList.push_back(node);

	// Ÿ�� ���� �ҷ�����
	auto tiles = GET_SINGLE(ObjMgr)->GetTiles();
	if (tiles == nullptr)
		return;

	// ���� Ÿ�� �˻� ��, ���Ƿ� Ÿ�� �ε����� ��� ��Ƶα� ���� ����
	int index = 0;

	while (true)
	{
		// ��
		index = node->idx - TILE_CNT_X; // �� ĭ ���� Ÿ�� �ε����� ����

		// �����ϴ� Ÿ������? (�ùٸ� �ε���)
		// �� �� �ִ� Ÿ������? (�浹 ����)
		// �̹� �����߰ų�, ������ ��� ���ԵǾ� �ִ� �༮�� ����
		//   -> Ŭ����, ���� ����Ʈ�� �̹� �����Ѵٸ� ����
		if (index >= 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			// Ÿ�� �ε����� �ش��ϴ� Ÿ�� ����(���)�� ���� ��,
			// ���� ����Ʈ(������ ���)�� �߰�
			openList.push_back(MakeNode(index, node, tiles));
		}

		// �Ʒ�
		index = node->idx + TILE_CNT_X;
		if (index < (TILE_CNT_X * TILE_CNT_Y)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ������ 
		index = node->idx + 1;
		if (index < (TILE_CNT_X * TILE_CNT_Y) && index % TILE_CNT_X != 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ���� 
		index = node->idx - 1;
		if (index >= 0 && (index % TILE_CNT_X != TILE_CNT_X - 1)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ������

		// ������ ��

		// ���� �Ʒ�

		// ������ �Ʒ�

		// ���� ����Ʈ�� ����
		//  -> ���(�Ÿ�)�� �������� �������� ����
		openList.sort(Compare);

		// ���� ����Ʈ�� ����ִٸ� ����
		if (openList.empty())
			return;

		// ���� ����Ʈ���� �ڽ�Ʈ�� ���� ���� ���� Ŭ�����Ʈ�� ����
		auto iter = openList.begin();
		node = *iter;

		closeList.push_back(*iter);
		openList.erase(iter);

		// �˻� ���� ����� Ÿ�� �ε����� �� �ε����� ���ٸ�
		if (node->idx == goalIdx)
		{
			// �� �ε����� �����ߴٴ� ���� ��θ� ã�Ҵٴ� ��
			// ����, ������ ��� �����͸� ��´�.
			while (true)
			{
				// �˻� ��忡 �����Ͽ� ����(�θ� ���� ����)���� Ÿ�� �ε����� ����
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
	// ���� or Ŭ���� ��Ͽ� �����Ѵٸ� false,
	// �ƴ϶�� true

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

	// �θ� �������� �Ÿ�
	float distanceX = (*tiles)[parent->idx]->posX - (*tiles)[idx]->posX;
	float distanceY = (*tiles)[parent->idx]->posY - (*tiles)[idx]->posY;

	float gCost = sqrt(distanceX * distanceX + distanceY * distanceY);

	// ���� �������� �Ÿ�
	float goalDistanceX = (*tiles)[goalIdx]->posX - (*tiles)[idx]->posX;
	float goalDistanceY = (*tiles)[goalIdx]->posY - (*tiles)[idx]->posY;

	float hCost = sqrt(goalDistanceX * goalDistanceX + goalDistanceY * goalDistanceY);

	node->fCost = gCost + hCost;

	return node;
}

void AStar::Release()
{
	// ���¸���Ʈ ����
	for (auto iter = openList.begin(); iter != openList.end(); ++iter)
		SafeDelete(*iter);
	openList.clear();

	// Ŭ�����Ʈ ����
	for (auto iter = closeList.begin(); iter != closeList.end(); ++iter)
		SafeDelete(*iter);
	closeList.clear();

	// ���� ��� ����
	bestList.clear();
}
