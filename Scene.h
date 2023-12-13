#pragma once
#include "Define.h"

class Prototype;
class Scene
{
protected:
	// �� ���� ������ü�� �����ϰ� ������ ��ü 
	Prototype* proto;

public:
	virtual HRESULT Initialize() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;

public:
	Scene();
	virtual ~Scene();
};

