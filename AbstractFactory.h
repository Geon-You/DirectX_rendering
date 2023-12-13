#pragma once

//class Object;
//// 실제 동적할당할 타입을 템플릿으로 받아옴
//template<typename T>
//// 추상 팩토리 패턴
//class AbstractFactory
//{
//public:
//	static Object* CreateObject()
//	{
//		Object* obj = new T();
//		obj->Initialize();
//
//		return obj;
//	}
//
//	static Object* CreateObject(int x, int y)
//	{
//		Object* obj = new T();
//		obj->Initialize();
//		obj->SetPos(x, y);
//
//		return obj;
//	}
//};