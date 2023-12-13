#include "TimeMgr.h"

TimeMgr::TimeMgr()
	:deltaTime(0)
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::Initialize(void)
{
	// 1�ʿ� cpu�� ī�����ϴ� ƽ ���� ������
	QueryPerformanceFrequency(&cpuTick);

	// ��ǻ�Ͱ� ���õ� ��, ������� ī���õ� ƽ ��
	// -> ���⼭ ������ ƽ ���� ū �ǹ̰� ����
	//	  Ÿ�̸Ӹ� �ʱ�ȭ�ϴ� ������ ƽ ī��Ʈ�� �Ʒ� ������ ���� �ʱ�ȭ
	//    ��Ÿ �ð� ������ ���� �Ʒ��� �������� ���������� ����ϱ� ����,
	//    �ʱ�ȭ�ϴ� �뵵�� ����ߴٰ� �����ϸ� ��
	QueryPerformanceCounter(&currentTime);
	QueryPerformanceCounter(&prevTime);

}

void TimeMgr::Update(void)
{
	// �ش� �Լ��� �ݺ��Ǵ� �������� ����ؼ� ȣ���Ѵٰ� ����

	// ����ؼ� ���ϴ� ���� ƽ���� ������
	QueryPerformanceCounter(&currentTime);

	// ��Ÿ Ÿ�� = (���� ƽ�� - ���� ƽ��) / �ʴ�ƽ��
	deltaTime = float(currentTime.QuadPart - prevTime.QuadPart) / (cpuTick.QuadPart * 0.001f);
	// ��Ÿ Ÿ���� �������Ƿ�, ���� ƽ���� ���� ƽ���� ����
	prevTime = currentTime;
}
