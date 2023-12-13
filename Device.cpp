#include "Device.h"

Device::Device(void)
	:direct(NULL)
	, device(NULL)
	, sprite(NULL)
	, font(NULL)
	, line(NULL)
{
}

Device::~Device(void)
{
	this->Release();
}

HRESULT Device::InitDevice(WINMODE mode)
{
	// 1. ���̷�Ʈ ��ü ����
	// 2. ���̷�Ʈ ��ü�� ���� ��ġ ���� ����
	// 3. ������ ��ġ ������ ���� ���� ó���� ���� ���� ����
	// 4. ���� ���� ���� �������� ����̽� ��ġ ����

	direct = Direct3DCreate9(D3D_SDK_VERSION);

	// ��ġ ���ɿ� ���� ������ ���� ����ü
	D3DCAPS9 devicecaps;
	ZeroMemory(&devicecaps, sizeof(D3DCAPS9));

	// ��ġ�� ������ �����Ѵ�.
	if (FAILED(direct->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devicecaps)))
	{
		ERR_MSG(g_hWnd, L"��ġ ���������� ����");
		return E_FAIL;
	}

	DWORD BehaviorFlag = 0;
	// �ϵ���� ���ؽ� ���μ��� ���� ���� Ȯ��
	if (devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// �����Ѵٸ� �ϵ���� ���ؽ� ���μ��� ���
		BehaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// �ƴ϶�� ����Ʈ���� ���ؽ� ���μ��� ���
		BehaviorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	// ���ǽ��� �Ʒ��� ���۵��� ����
	// 1. ������Ʈ�� or �̹��� ó���� ���� ������ �ȼ� (�÷� ���� -> ����/�ĸ� ����)
	// 2. ����/���ٽ� ���� (����/���ٽ� ����)

	// ����(����Ʈ) ���� : ���� ������ ��ġ�� ��µǰ� �ִ� �޸� ����
	// �ĸ�(��) ���� : ��� �ӵ��� ����� ���� ����Ʈ ���ۿ� ������ ���� ������
	//					�����ϰ� �ִ� �޸� ����
	//					�÷� ���� -> �ȼ� ���� 
	//					���� ���� -> ���ο� �ȼ��� �÷� ���ۿ� ���� �� ���ΰ��� ����
	//								 �Ǻ� ��  (���� z ��, ���� z buffer ��� ��)
	//					���ٽ� ���� -> ���� ���ۿ� ���, Ư�� ������ �׸����� ���� ���� (���� masking ��)

	// ������ ����� ����/�ĸ� �� ����/���ٽ� ���ۿ� ���� ���� ���� ���� ����ü
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// �ĸ� ���� ����
	d3dpp.BackBufferWidth = WIN_SIZE_X;
	d3dpp.BackBufferHeight = WIN_SIZE_Y;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// ���� �� ���ٽ� ���� ����
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	// ���������� ������ �������� �ڵ��� ���� 
	d3dpp.hDeviceWindow = g_hWnd;
	// ������ ��� (â, Ǯ)
	d3dpp.Windowed = mode;
	
	// ����ü�� -> ������ ���ǽ��� �ϳ��� �÷������� ����
	// ���ǽ�1    ���ǽ�2
	// ���� ����  �ĸ� ����
	// ���ǽ�2    ���ǽ�1
	// ���� ����  �ĸ� ����

	// ���� ü�� (���� ���۸�) ��ȯ ����� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	
	// ȭ�� ����� ����(ȭ���� ���� ��ġ�� �ӵ�) (â���� 0, Ǯ��ũ���̸� �����ϴ� hz ����)
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// �ĸ� ���۸� ���� ���ۿ� ǥ���� �� �ִ� �ִ� �ӵ�
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// ��ġ ����
	if (FAILED(direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, g_hWnd, BehaviorFlag, &d3dpp, &device)))
	{
		ERR_MSG(g_hWnd, L"��ġ���� ����");
		return E_FAIL;
	}

	// ��������Ʈ ��ü ����
	if (FAILED(D3DXCreateSprite(device, &sprite)))
	{
		return E_FAIL;
	}

	// ��Ʈ ������ ���� ����ü
	D3DXFONT_DESC tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(tFontInfo));

	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");

	// ��Ʈ ����
	if (FAILED(D3DXCreateFontIndirect(device, &tFontInfo, &font)))
	{
		ERR_MSG(g_hWnd, L"��Ʈ���� ����");
	}

	if (FAILED(D3DXCreateLine(device, &line)))
	{
		ERR_MSG(g_hWnd, L"���λ��� ����");
	}

	return S_OK;
}

//1. ȭ���� Clear() �Լ��� �ʱ�ȭ �Ѵ�.
//2. ����� �ĸ� ���ۿ� �׸��� ���� ����̽��� BeginScene() �Լ��� ȣ���Ѵ�.
//3. ����� �׸���.
//4. ����� �� �׷ȴٴ� ���� EndScene() �Լ��� �˸���.
//5. Present() �Լ��� ���� ���ۿ� �ĸ� ���۸� ��ü�Ѵ�.
//6. 1���� 5�� �ݺ��Ѵ�
void Device::RenderBegin()
{
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	device->BeginScene();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Device::RenderEnd()
{
	sprite->End();
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

void Device::Release()
{
	sprite->Release();
	device->Release();
	direct->Release();
}
