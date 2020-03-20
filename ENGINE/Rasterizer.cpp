#include "Rasterizer.h"



Rasterizer::Rasterizer()
{
}


Rasterizer::~Rasterizer()
{
	if (nullptr != state)
	{
		state->Release();
		state = nullptr;
	}
}

bool Rasterizer::Create()
{
	//typedef struct D3D11_RASTERIZER_DESC
//{
//	D3D11_FILL_MODE FillMode;
//	D3D11_CULL_MODE CullMode;
//	BOOL FrontCounterClockwise;
//	INT DepthBias;
//	FLOAT DepthBiasClamp;
//	FLOAT SlopeScaledDepthBias;
//	BOOL DepthClipEnable;
//	BOOL ScissorEnable;
//	BOOL MultisampleEnable;
//	BOOL AntialiasedLineEnable;
//} 	D3D11_RASTERIZER_DESC;

// m_Decs.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
// �ڽ� ����� ����.
// ���Ǿ� ����� ����.
	desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	// ���� �����Ŵ�.
	// m_Decs.DepthBias \ 

	desc.MultisampleEnable = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	return Create(desc);
}

bool Rasterizer::Create(const D3D11_RASTERIZER_DESC& _Desc)
{
	if (&desc != &_Desc)
	{
		desc = _Desc;
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateRasterizerState(&desc, &state))
	{
		BOOM;
		return false;
	}

	return true;

}



void Rasterizer::Update()
{
	GraphicDevice::Inst()->GetDXContext()->RSSetState(state);
}
