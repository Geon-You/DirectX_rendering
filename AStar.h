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
	list<NODE*> openList;  // �����ؾ��� ����
	list<NODE*> closeList; // �̹� ������ ����
	list<int> bestList;    // ������ ������ ����� Ÿ�ϵ��� �ε���

public:
	int startIdx; // ��ã�⸦ ������ Ÿ���� �ε��� (���� ĳ���Ͱ� �ִ� Ÿ��)
	int goalIdx;  // ��ǥ Ÿ���� �ε��� (���콺�� Ŭ���� Ÿ��)

public:
	// ��ã�� ���� ��, ȣ���� �Լ�
	void AstarStart(int _startIdx, int _goalIdx);
	// ���� ��θ� �����ϴ� �Լ�
	void MakeRoute();
	// �Ķ���ͷ� Ư�� Ÿ���� �ε����� �޾�, �ش� Ÿ����
	// ���� or Ŭ���� ����Ʈ�� �̹� �����ϴ��� Ȯ���ϴ� �Լ�
	bool CheckList(int idx);
	// ��� ������ ������ ���� �Լ�
	NODE* MakeNode(int idx, NODE* parent, const vector<TILE*>* tiles);
	void Release();
	// ���� ��θ� ���� ����� �ּҸ� ��ȯ
	list<int>* GetBestList() { return &bestList; }

public:
	static bool Compare(NODE* a, NODE* b)
	{
		return a->fCost < b->fCost;
	}
};

