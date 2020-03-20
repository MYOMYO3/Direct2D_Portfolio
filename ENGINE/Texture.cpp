#include "Texture.h"
#include <File.h>


Texture::Texture() :renderTargetView(nullptr), depthStencilView(nullptr), shaderResourceView(nullptr), texture(nullptr)
{
	
}


Texture::~Texture()
{
	image.Release();

	// �ؽ�ó�� ������ �������� �̾Ƴ����Ƿ� �׻� �����Ϸ���
	// ��������
	if (nullptr != renderTargetView)	{ renderTargetView->Release();		renderTargetView	= nullptr; }
	if (nullptr != depthStencilView)	{ depthStencilView->Release();		depthStencilView	= nullptr; }
	if (nullptr != shaderResourceView)	{ shaderResourceView->Release();	shaderResourceView	= nullptr; }
	if (nullptr != texture)				{ texture->Release();				texture				= nullptr; }
}
void Texture::Update(Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	if (nullptr == shaderResourceView)
	{
		BOOM;
	}

	// _SetIndex ���õǴ� ��ġ
	// �� ��ġ���� �������� � �����ҷ�????

	switch (_ShaderType)
	{
	case Shader::SHTYPE_VS:
		GraphicDevice::Inst()->GetDXContext()->VSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_HS:
		GraphicDevice::Inst()->GetDXContext()->HSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_DS:
		GraphicDevice::Inst()->GetDXContext()->DSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_GS:
		GraphicDevice::Inst()->GetDXContext()->GSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_PS:
		GraphicDevice::Inst()->GetDXContext()->PSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	default:
		BOOM;
		break;
	}
}



bool Texture::Load()
{
	if (nullptr == GraphicDevice::Inst()->GetDXDevice())
	{
		BOOM;
		return false;
	}

	if (true == file.CheckExtension(L"DDs") || file.CheckExtension(L"dds"))
	{
		if (S_OK != DirectX::LoadFromDDSFile(file.GetFullPathString().c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image))
		{
			BOOM;
			return false;
		}
	}
	else if (true == file.CheckExtension(L"TGA") || file.CheckExtension(L"tga"))
	{
		if (S_OK != DirectX::LoadFromTGAFile(file.GetFullPathString().c_str(), nullptr, image))
		{
			BOOM;
			return false;
		}
	}
	else // if (true == m_File.IsExt(L"Png") || m_File.IsExt(L"png"))
	{
		if (S_OK != DirectX::LoadFromWICFile(file.GetFullPathString().c_str()
			, DirectX::WIC_FLAGS_NONE, nullptr, image))
		{
			BOOM;
			return false;
		}
	}

	if (0 == image.GetImageCount())
	{
		BOOM;
		return false;
	}

	
// ���̴��� �������ټ� �ִ� ������ ���´�.
	if (S_OK != DirectX::CreateShaderResourceView(GraphicDevice::Inst()->GetDXDevice()
		, image.GetImages()
		, image.GetImageCount()
		, image.GetMetadata()
		, &shaderResourceView))
	{
		BOOM;
		return false;
	}

	return true;
}