#pragma once
#include <SmartPtr.h>

#include "Resources.h"
#include "MeshData.h"
#include "GraphicDevice.h"

#include <vector>

class Mesh : public Resources
{
private:
	//�̷� ���ؽ� ���ۿ� �ε��� ���۰�
	//���̷�Ʈ�� �������̽��� ����κ� �׷��� �Ǿ��ִ�.
	//�־��ָ� �츮�� �����޴� ������ �Ǿ��ִ�.
	//���̷�Ʈ 11���ʹ� ��κ� ���� ���鶧 �뵵�� ���ý� ��������
	//�ε��� �������� ��������

	//���ؽ� ���ۿ� �ε��� �����̴�.
	// �������̽��� �߻�Ŭ����ó�� ��������� �Ǿ���.
	//�ϳ��� �ٰ����� ����� �ִ� ����

	// {100, 200, 300} {150, 250, 350} {250, 450, 350}
	// {200, 300, 300} {150, 250, 350} {250, 450, 350}
	// ID3D11Buffer* m_VB;

	// {0, 1, 2}
	// �� �ٰ����� ����� �ִ� ������ �׸��� ������ ���� ������
	// ID3D11Buffer* m_IB;

private:
	class VertexBuffer : public ControlBlock
	{
	public:
		ID3D11Buffer* vtxBuffer;
		D3D11_BUFFER_DESC vtxDesc;
		UINT vtxSize;	//�� �ϳ��� x����Ʈ�� ũ���̴�.
		UINT vtxCount;	//���� x ����

		VertexBuffer() :vtxBuffer(nullptr) {}
		~VertexBuffer()
		{
			if (nullptr != vtxBuffer)
			{
				vtxBuffer->Release();
				vtxBuffer = nullptr;
			}
		}
	};

	class IndexBuffer : public ControlBlock
	{
	public:
		ID3D11Buffer* indexBuffer;
		D3D11_BUFFER_DESC indexDesc;
		DXGI_FORMAT indexBufferType;	//�ε��� ���� Ÿ�� �ڷ���
		UINT indexSize;	//�ε��� ���� ���� 1���� ������.
		UINT indexCount;	//���� x ���� ��ü �׳� ������ ���??

		IndexBuffer() :indexBuffer(nullptr) {}
		~IndexBuffer()
		{
			if (nullptr != indexBuffer)
			{
				indexBuffer->Release();
				indexBuffer = nullptr;
			}
		}
	};


private:
	//�� ��带 �ٲ��ָ� ���� ��ų� �� �������� �����ѵ�
	//�װ� ���� ����
	D3D11_PRIMITIVE_TOPOLOGY drawMode;	//�⺻���� ������ input assembler

	std::vector<My_Ptr<VertexBuffer>>	arrVB;
	std::vector<My_Ptr<IndexBuffer>>	arrIB;	//�ε������� ���̵� ����� �׸��� �ִ�.

//public:
//	void DrawModeChange(D3D11_PRIMITIVE_TOPOLOGY _DrawMode)
//	{
//		drawMode = _DrawMode;
//	}
public:
	template<typename VT, typename IT>
	bool Create(std::vector<VT>& _VtxData, D3D11_USAGE _VtxUsage, std::vector<IT>& _IdxData, D3D11_USAGE _IdxUsage)
	{
		bool Check = false;

		Check = CreateVB((int)_VtxData.size(), VT::MemorySize(), _VtxUsage, &_VtxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		Check = CreateIB(IT::Format(), (int)_IdxData.size() * IT::MemCount(), IT::MemorySize(), _IdxUsage, &_IdxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		return true;
	}

	template<typename VBTYPE>
	bool Create(std::vector<VBTYPE>& _VtxData, D3D11_USAGE _VtxUsage, std::vector<DWORD>& _IdxData, D3D11_USAGE _IdxUsage)
	{
		bool Check = false;

		Check = CreateVB((int)_VtxData.size(), VBTYPE::MemorySize(), _VtxUsage, &_VtxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		Check = CreateIB(DXGI_FORMAT_R32_UINT, (int)_IdxData.size(), sizeof(DWORD), _IdxUsage, &_IdxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		return true;
	}

public:
	template<typename T>
	bool CreateVB(std::vector<T>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}

		return CreateVB((UINT)_Data.size(), T::MemorySize(), _VtxUsage, &_Data[0]);
	}
	bool CreateVB(UINT _VtxCount, UINT _VtxSize, D3D11_USAGE _VtxUsage, void* _Data);

	template<typename T>
	bool CreateIB(std::vector<T>& _Data, D3D11_USAGE _IdxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}

		return CreateIB(T::Format(), (UINT)_Data.size() * 3, T::MemorySize(), _IdxUsage, &_Data[0]);
	}

	bool CreateIB(std::vector<DWORD>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}

		return	CreateIB(DXGI_FORMAT_R32_UINT , (UINT)_Data.size(), sizeof(DWORD), _VtxUsage, &_Data[0]);
	}

	bool CreateIB(DXGI_FORMAT _IdxFormat, UINT _IdxCount, UINT _IdxSize, D3D11_USAGE _IdxUsage, void* _Data);

public:
	void Update(UINT _VtxIndex, UINT _IdxIndex);
	void Render(UINT _VtxIndex, UINT _IdxIndex);

	void RenderAuto();

public:
	Mesh();
	~Mesh();
};

