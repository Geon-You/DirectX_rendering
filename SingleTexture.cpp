#include "SingleTexture.h"
#include "Device.h"

SingleTexture::SingleTexture()
	: texInfo(nullptr)
{
}

SingleTexture::~SingleTexture()
{
	Release();
}

const TEXINFO* SingleTexture::GetTexture(const TCHAR* key, const int& cnt)
{
	return texInfo;
}

HRESULT SingleTexture::InsertTexture(const TCHAR* path, const TCHAR* key, const int& cnt)
{
	texInfo = new TEXINFO;
	ZeroMemory(texInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(path, &texInfo->ImgInfo)))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		GET_SINGLE(Device)->GetDevice() // ��ġ ��ü ����
		, path // �̹��� ���� ���
		, texInfo->ImgInfo.Width // �̹��� �ʺ�
		, texInfo->ImgInfo.Height // �̹��� ����
		, 1 // �̹��� �Ӹ� ����
		, 0 // �ؽ��� ��� ��� ����
		, texInfo->ImgInfo.Format // �̹��� ����
		, D3DPOOL_MANAGED // �ؽ��Ŀ� ���� �޸� ���� ��� ����
		, D3DX_DEFAULT // �ؽ��� ���͸� ��� ����
		, D3DX_DEFAULT // �Ӹ� �ؽ��� ���͸� ��� ����
		,  D3DCOLOR_ARGB(255, 255, 0, 255)	// �����ϰ� ���� ���� ����
		, &texInfo->ImgInfo // �̹��� ���� ����
		, NULL // �ش� �̹����� ����ϴ� r,g,b,a ä�� �� ���� ���� ���� ���� ����ü ������
		, &texInfo->texture))) // ������ �ؽ��� ��ü�� ���� ����ü ������
	{
		return E_FAIL;
	}

	return S_OK;
}

void SingleTexture::Release()
{
	if (texInfo)
	{
		texInfo->texture->Release();
		delete texInfo;
		texInfo = nullptr;
	}
}
