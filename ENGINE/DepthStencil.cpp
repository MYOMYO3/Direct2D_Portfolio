#include "DepthStencil.h"



DepthStencil::DepthStencil()
{
}


DepthStencil::~DepthStencil()
{
	if (nullptr != state)
	{
		state->Release();
		state = nullptr;
	}
}


bool DepthStencil::Create()
{
	// ������ ����Ѵ�.
	// 2D�����̸�
	// ���� �׷����� ���� �ڿ� ���� ���̴�.
	desc.DepthEnable = TRUE;

	// �׸��� ���̰��� ���Ҷ�
	// �ȼ����̴����� ���� ó�� �ؾ��Ѵٰ� ������� �ϴµ�. 
	// ���ο� �ȼ��� ���̰���
	// ������ ���̰����� ������.

	// 2D�����̸�
	// ���� �׷����� ���� �ڿ� ���� ���̴�.
	desc.DepthFunc = D3D11_COMPARISON_LESS;

	// ���θ� ���⸸ �ϰ� 
	// ���� �������� �ʴ´�. 
	// ������ ������ ���ؼ��� 
	// Z���� ������ 
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;


	//BOOL DepthEnable;
	//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
	//D3D11_COMPARISON_FUNC DepthFunc;
	// BOOL StencilEnable;
	// UINT8 StencilReadMask;
	// UINT8 StencilWriteMask;
	// D3D11_DEPTH_STENCILOP_DESC FrontFace;
	// D3D11_DEPTH_STENCILOP_DESC BackFace;

	//typedef struct D3D11_DEPTH_STENCILOP_DESC
	//{
	//	D3D11_STENCIL_OP StencilFailOp;
	//	D3D11_STENCIL_OP StencilDepthFailOp;
	//	D3D11_STENCIL_OP StencilPassOp;
	//	D3D11_COMPARISON_FUNC StencilFunc;
	//} 	D3D11_DEPTH_STENCILOP_DESC;

	//D3D11_STENCIL_OP_KEEP = 1,
	//D3D11_STENCIL_OP_ZERO = 2,
	//D3D11_STENCIL_OP_REPLACE = 3,
	//D3D11_STENCIL_OP_INCR_SAT = 4,
	//D3D11_STENCIL_OP_DECR_SAT = 5,
	//D3D11_STENCIL_OP_INVERT = 6,
	//D3D11_STENCIL_OP_INCR = 7,
	//D3D11_STENCIL_OP_DECR = 8


	// �����޽�.
	desc.StencilEnable = FALSE;

	return Create(desc);
}

bool DepthStencil::Create(const D3D11_DEPTH_STENCIL_DESC& _Desc)
{
	if (&desc != &_Desc)
	{
		desc = _Desc;
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateDepthStencilState(&desc, &state))
	{
		BOOM;
		return false;
	}

	return true;
}

void DepthStencil::Update()
{
	GraphicDevice::Inst()->GetDXContext()->OMSetDepthStencilState(state, 0);
}
