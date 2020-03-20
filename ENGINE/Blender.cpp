#include "Blender.h"
#include "GraphicDevice.h"


Blender::Blender() : color(1.0f)
{
}


Blender::~Blender()
{
	if (nullptr != state)
	{
		state->Release();
		state = nullptr;
	}
}

bool Blender::Create()
{
#pragma region remark
	// ���� �Ұų� 
	// false�� �Ѱ��� ����ϰڴٶ�� �̾߱�
	// ���� 0���� ����ϰڴ�.
	// ����Ÿ���� �������� 0���� ���� ��ĸ��� �̿��ϰڴٴ� ����
	// ���� ������ �༮���� ������ ���ϰڴٴ� ���� �ƴϴ�.
	//BOOL BlendEnable;
	//D3D11_BLEND SrcBlend;
	//D3D11_BLEND DestBlend;
	//D3D11_BLEND_OP BlendOp;
	//D3D11_BLEND SrcBlendAlpha;
	//D3D11_BLEND DestBlendAlpha;
	//D3D11_BLEND_OP BlendOpAlpha;
	//UINT8 RenderTargetWriteMask;
	//AlphaToCoverageEnable	FALSE
	//IndependentBlendEnable	FALSE
	//RenderTarget[0].BlendEnable	FALSE
	//RenderTarget[0].SrcBlend	D3D11_BLEND_ONE
	//RenderTarget[0].DestBlend	D3D11_BLEND_ZERO
	//RenderTarget[0].BlendOp	D3D11_BLEND_OP_ADD
	//RenderTarget[0].SrcBlendAlpha	D3D11_BLEND_ONE
	//RenderTarget[0].DestBlendAlpha	D3D11_BLEND_ZERO
	//RenderTarget[0].BlendOpAlpha	D3D11_BLEND_OP_ADD
	//RenderTarget[0].RenderTargetWriteMask	D3D11_COLOR_WRITE_ENABLE_ALL
	// https://docs.microsoft.com/ko-kr/windows/desktop/api/d3d11/ne-d3d11-d3d11_blend
	//typedef enum D3D11_BLEND {
	//	D3D11_BLEND_ZERO,
	//	D3D11_BLEND_ONE,
	//	D3D11_BLEND_SRC_COLOR,
	//	D3D11_BLEND_INV_SRC_COLOR,
	//	D3D11_BLEND_SRC_ALPHA,
	//	D3D11_BLEND_INV_SRC_ALPHA,
	//	D3D11_BLEND_DEST_ALPHA,
	//	D3D11_BLEND_INV_DEST_ALPHA,
	//	D3D11_BLEND_DEST_COLOR,
	//	D3D11_BLEND_INV_DEST_COLOR,
	//	D3D11_BLEND_SRC_ALPHA_SAT,
	//	D3D11_BLEND_BLEND_FACTOR,
	//	D3D11_BLEND_INV_BLEND_FACTOR,
	//	D3D11_BLEND_SRC1_COLOR,
	//	D3D11_BLEND_INV_SRC1_COLOR,
	//	D3D11_BLEND_SRC1_ALPHA,
	//	D3D11_BLEND_INV_SRC1_ALPHA
	//};
#pragma endregion

	desc.AlphaToCoverageEnable					= false;								//��Ƽ���ø����� ����Ÿ�Ͽ� �ȼ����� �����Ҷ��� ���İ��� ��������� �����ϴ� ���̴�.
	desc.IndependentBlendEnable					= false;							//FALSE�� �����ϸ� ����Ÿ�� 0�� �������� ����Ͽ� ����Ÿ�� 1~7������ ������ ���� �ȴ�.
	desc.RenderTarget[0].BlendEnable			= true;								//�ȼ� ���̴��� ���� ����Ÿ���� ���� ���� ó���� ���� ������ �����ϸ� ����Ÿ�ٸ��� �����Ҽ� �ִ�.
	desc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;		//����Ÿ���� ������� ������ �����Ѵ�. 
	desc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ZERO;

	//desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//����Ÿ���� ������� ������ �����Ѵ�. 
	//desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	return Create(desc);
}

bool Blender::Create(D3D11_BLEND _SrcBlend, D3D11_BLEND _DestBlend, D3D11_BLEND _SrcAlpha, D3D11_BLEND _DestAlpha)
{
	desc.AlphaToCoverageEnable = true;								//��Ƽ���ø����� ����Ÿ�Ͽ� �ȼ����� �����Ҷ��� ���İ��� ��������� �����ϴ� ���̴�.
	desc.IndependentBlendEnable = false;							//FALSE�� �����ϸ� ����Ÿ�� 0�� �������� ����Ͽ� ����Ÿ�� 1~7������ ������ ���� �ȴ�.
	desc.RenderTarget[0].BlendEnable = true;								//�ȼ� ���̴��� ���� ����Ÿ���� ���� ���� ó���� ���� ������ �����ϸ� ����Ÿ�ٸ��� �����Ҽ� �ִ�.
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//����Ÿ���� ������� ������ �����Ѵ�. 
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlend = _SrcBlend;
	desc.RenderTarget[0].DestBlend = _DestBlend;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = _SrcAlpha;
	desc.RenderTarget[0].DestBlendAlpha = _DestAlpha;

	//desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//����Ÿ���� ������� ������ �����Ѵ�. 
	//desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	return Create(desc);
}

void Blender::SetBlendOneAndOne()
{
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
}

bool Blender::Create(const D3D11_BLEND_DESC& _Desc)
{
	if (&desc != &_Desc)
	{
		desc = _Desc;
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBlendState(&desc, &state))
	{
		BOOM;
		return false;
	}

	return true;
}

void Blender::Update()
{

	GraphicDevice::Inst()->GetDXContext()->OMSetBlendState(state, color.Arr, 0xffffffff);	//BlendFactor �� D3D11_BLEND_FACTOR���� ����� ������� RGBA���� ������ �迭�̸�
																							//SampleMask�� ��Ƽ���� ����Ÿ�ٿ��� � ���÷� Enable�� �ұ�?(Msking)�� �����ϴ� ��
}
