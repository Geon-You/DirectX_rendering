#pragma once
#include "Include.h"

class MainGame
{
public:
	HRESULT Initialize(); // �ʱ�ȭ
	void Update(); // ���� �� ���� ����
	void Render(); // ���� �� �׸���
	void Release(); // �޸� ����

public:
	MainGame();
	~MainGame();
};

