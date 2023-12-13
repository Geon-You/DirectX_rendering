#pragma once

// tŸ�� ��ü �޸� ���� �Լ�
template <typename T>
inline void SafeDelete(T& instance)
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

// �̱��� ��ũ��ȭ
#define DECLARE_SINGLETON(type)public:	\
	static type** GetInstance(void)		\
	{                                   \
		static type* pInstance = new type;\
		if (pInstance == NULL)          \
		     pInstance = new type;      \
	    return &pInstance;				\
	}                                   \
	static void Destroy(void)	\
	{                                   \
		type** ppInstance = GetInstance();\
		if(*ppInstance != NULL)			\
		{                               \
			delete *ppInstance;			\
			*ppInstance = NULL;			\
		}                               \
	}

#define GET_SINGLE(type) (*type::GetInstance())

#define ERR_MSG(hWnd, sz) MessageBox(hWnd, sz, L"system err", MB_OK)