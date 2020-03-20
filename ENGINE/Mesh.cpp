#include "Mesh.h"



Mesh::Mesh() : drawMode(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}


Mesh::~Mesh()
{
}

bool Mesh::CreateVB(UINT _VtxCount, UINT _VtxSize, D3D11_USAGE _VtxUsage, void* _Data)
{
	arrVB.resize(arrVB.size() + 1);					//�迭�� ī�Ľ�Ƽ�� �ø��� ���Ҵ� �þ�� �ʴ°� ������
	VertexBuffer* newVB = new VertexBuffer();		//�迭�� �ø��°��� �ƴ϶� ���� ����ü�� �ø��°��� ��������
	arrVB[arrVB.size() - 1] = newVB;

	newVB->vtxCount = _VtxCount;	//4����	
	newVB->vtxSize = _VtxSize;		//16����Ʈ

	newVB->vtxDesc.ByteWidth = _VtxCount * _VtxSize;
	newVB->vtxDesc.Usage = _VtxUsage;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == newVB->vtxDesc.Usage)
	{
		newVB->vtxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	newVB->vtxDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//�ʱ� �����͸� �־��ٶ� �������ִ� ����ü
	D3D11_SUBRESOURCE_DATA dataStruct = D3D11_SUBRESOURCE_DATA();
	dataStruct.pSysMem = _Data;

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBuffer(&newVB->vtxDesc, &dataStruct, &newVB->vtxBuffer))
	{
		BOOM;
		return false;
	}

	return true;
}

bool Mesh::CreateIB(DXGI_FORMAT _IdxFormat, UINT _IdxCount, UINT _IdxSize, D3D11_USAGE _IdxUsage, void* _Data)
{
	// �迭�� ī�Ľ�Ƽ�� �ø��� ���Ҵ� �þ�� �ʴ°�
// ������.

// �迭�� �ø��°��� �ƴ϶� ���� ����ü�� �ø��°���
// ��������
	arrIB.resize(arrIB.size() + 1);
	IndexBuffer* newIB = new IndexBuffer();
	arrIB[arrIB.size() - 1] = newIB;

	newIB->indexCount = _IdxCount; // 4����
	newIB->indexSize = _IdxSize; // 16����Ʈ
	newIB->indexBufferType = _IdxFormat; // 16����Ʈ

	// �ʱ�ȭ�� ��� ���� ������ ����.
	// �̻��ϸ� ���� 
	// NewVB->m_Desc

	newIB->indexDesc.ByteWidth = _IdxCount * _IdxSize;
	// �̰� �׷���ī�尡 �����ұ� �ƴϸ� CPU�� �Ҵ��ұ� �� �̷��͵�
	// �׸��� �����Ҷ� �����Ҽ� �ְ� �Ұž�????
	newIB->indexDesc.Usage = _IdxUsage;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == newIB->indexDesc.Usage)
	{
		newIB->indexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	newIB->indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// �ʱⵥ���͸� �־��ٶ� �������ִ� ����ü
	D3D11_SUBRESOURCE_DATA DataStruct = D3D11_SUBRESOURCE_DATA();
	DataStruct.pSysMem = _Data;

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBuffer(&newIB->indexDesc, &DataStruct, &newIB->indexBuffer))
	{
		BOOM;
		return false;
	}

	return true;
}
void Mesh::Update(UINT _VtxIndex, UINT _IdxIndex)
{
	UINT offSet = 0;
	UINT idxOffSet = 0;

	GraphicDevice::Inst()->GetDXContext()->IASetVertexBuffers(0, 1, &arrVB[_VtxIndex]->vtxBuffer, &arrVB[_VtxIndex]->vtxSize, &offSet);
	GraphicDevice::Inst()->GetDXContext()->IASetIndexBuffer(arrIB[_IdxIndex]->indexBuffer, arrIB[_IdxIndex]->indexBufferType, idxOffSet);
}

void Mesh::Render(UINT _VtxIndex, UINT _IdxIndex)
{
	//���⼭ �ؾ��ϳ� �����غ���
	//if (D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED == drawMode)
	//{
	//	BOOM;
	//}
	////������ �� ���� �Ǿ���.
	////������ ������������ �����ϰڴ�.
	//GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(drawMode);
	

	//���ؽ� ���ۿ� �ε��� ���۸� ����������Ѵ�.
	// �̰ǿ� 2�������ͳĸ� 2�����迭�� �־�޶�� �ǹ�
	//0 4��¥�� ���ؽ�����
	//1 3��¥�� ���ؽ�����
	//Offset�̰� ���ϵǴ°�
	//offset �װ�¥�� �߿��� 3���� �׷���

	//0, 0�� �����ϰڴ�
	//1, ���� �������ַ��°��� vb 1��¥����.
	// &m_ArrVB[_VtxIndex]->m_VB �׳༮�� vb�� �����ּ�
	// &m_ArrVB[_VtxIndex]->m_VTXSize m_ArrVB[_VtxIndex]->m_VTXSize ������
	// &Offset ������
	
	// �̳༮�� �ε��� ���۸� ����ϼ� �׸��ڴٴ� �̾߱�

	// 
	GraphicDevice::Inst()->GetDXContext()->DrawIndexed(arrIB[_IdxIndex]->indexCount, 0, 0);
}

void Mesh::RenderAuto()
{
	GraphicDevice::Inst()->GetDXContext()->DrawAuto();
}