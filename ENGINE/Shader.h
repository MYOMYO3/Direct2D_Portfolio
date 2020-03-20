#pragma once
#include "Resources.h"
#include "GraphicDevice.h"

//�װŴ� 
//���ؽ�
//��
//�����ν��̴�
//���� ���̴�
//�ȼ����̴�



class Shader : public Resources
{
public:
	enum SHADERTYPE
	{
		SHTYPE_VS,
		SHTYPE_HS,
		SHTYPE_DS,
		SHTYPE_GS,
		SHTYPE_PS,
	};

public:
	static UINT SizeOfFormat(DXGI_FORMAT _Format);

protected:
	static char vtxBufferText[256];

	//���̴��� �������� ��ũ��Ʈ ����� �����ص� �ȴ�.
	//�׷� ��ũ��Ʈ ����
	//� ���� ���μ����� ���α׷��� ��� ���� ����
	//�����Ϸ��� ���뿡 Ưȭ�� ��
	//�ƿ� �Ӱ��� ��ȭ�� ���õ� �κ��� �ϰ�¥
	// ��ũ��Ʈ ���� ���������� ���� �̷������.
	//�߰��߰� ���Ӱ� �о ���ο� �ڵ� ��ġ�� ������/
	// ���̴��� ������ �ִ�.
	//�׷���ī�帶�� �������� ���ϴ� ������ ������ �ִ�.
	//���̴� ������ �ϴ� 5.0�� ����Ұǵ�

	SHADERTYPE Type;

	ID3DBlob* blob;
	ID3DBlob* errorBlob;

	UINT versionHigh;//version high	//5
	UINT versionLow;//version low	//0

public:
	virtual void Update() = 0;

public:
	Shader(SHADERTYPE _Type);
	~Shader();
};

