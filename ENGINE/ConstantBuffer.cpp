#include "ConstantBuffer.h"



ConstBuffer::ConstBuffer() : constantBuffer(nullptr), Data(nullptr), reg(0)
{
}


ConstBuffer::~ConstBuffer()
{
	if (nullptr != Data)
	{
		delete[](char*)Data;
		Data = nullptr;
	}

	if (nullptr != constantBuffer)
	{
		constantBuffer->Release();
		constantBuffer = nullptr;
	}
}

bool ConstBuffer::Create(Shader::SHADERTYPE _SHType, UINT _Byte, UINT _Reg)
{
	reg = _Reg;

	switch (_SHType)
	{
	case Shader::SHTYPE_VS:
		SHUpdateFunc = &ConstBuffer::VSUpdate;
		break;
	case Shader::SHTYPE_HS:
		SHUpdateFunc = &ConstBuffer::HSUpdate;
		break;
	case Shader::SHTYPE_DS:
		SHUpdateFunc = &ConstBuffer::DSUpdate;
		break;
	case Shader::SHTYPE_GS:
		SHUpdateFunc = &ConstBuffer::GSUpdate;
		break;
	case Shader::SHTYPE_PS:
		SHUpdateFunc = &ConstBuffer::PSUpdate;
		break;
	default:
		break;
	}

	//�����͸� �����Ҵ����� ������ �ִ´�.
	bufferDesc.ByteWidth = _Byte;
	Data = new char[_Byte];
	//�̰� �׷���ī�尡 �����ұ� �ƴϸ� CPU�� �Ҵ��ұ� ���� �̷��͵�
	//�׸���  �����Ҷ� �����Ҽ� �ְ� �Ҳ���??

	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	if (bufferDesc.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	subResouceData.pSysMem = Data;
	mapSubResource.pData = Data;

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBuffer(&bufferDesc, &subResouceData, &constantBuffer))
	{
		BOOM;
		return false;
	}

	return true;
}

void ConstBuffer::DataSetting(void* _Data, UINT _Size)
{
	//�����ϴ� ���� ����̽� �̱� ������
	//���ؽ�Ʈ���� ��û�ؾ� �Ѵ�.
	//��� ����̽����� ���߰� �� �����͸� ��������
	//�� ������ ����� �־����/
	GraphicDevice::Inst()->GetDXContext()->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapSubResource);
	memcpy_s(mapSubResource.pData, bufferDesc.ByteWidth, _Data, _Size);	//��� ����
	GraphicDevice::Inst()->GetDXContext()->Unmap(constantBuffer, 0);
}

void ConstBuffer::Update()
{
		

	(this->*SHUpdateFunc)();
}

void ConstBuffer::VSUpdate() { GraphicDevice::Inst()->GetDXContext()->VSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::HSUpdate() { GraphicDevice::Inst()->GetDXContext()->HSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::DSUpdate() { GraphicDevice::Inst()->GetDXContext()->DSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::GSUpdate() { GraphicDevice::Inst()->GetDXContext()->GSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::PSUpdate() { GraphicDevice::Inst()->GetDXContext()->PSSetConstantBuffers(reg, 1, &constantBuffer); }