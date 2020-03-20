#include "PixelShader.h"



PxlShader::PxlShader() : Shader(Shader::SHADERTYPE::SHTYPE_PS), pixelShader(nullptr)
{
}


PxlShader::~PxlShader()
{
	if (nullptr != pixelShader)
	{
		pixelShader->Release();
		pixelShader = nullptr;
	}
}

bool PxlShader::Load(UINT _VH, UINT _VL, const char* _FuncName)
{
	versionHigh = _VH;
	versionLow = _VL;

	UINT flag = 0;

#ifdef _DEBUG 
	flag = D3D10_SHADER_DEBUG;
#endif

	sprintf_s(vtxBufferText, "ps_%d_%d", versionHigh, versionLow);


	// ����ܰ迡������ �� ������ ����� �Ұ����� ���δ�.
	if (
		S_OK != D3DCompileFromFile
		(
			file.GetFullPath(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_FuncName,
			vtxBufferText,
			flag, // ����׸���϶� ����� ����� ���� �˷��ش�.
			0, // ������ �𸣰���
			&blob,
			&errorBlob
		)
		)
	{
		std::string ErrorText = (char*)errorBlob->GetBufferPointer();

		Debug::Inst().ConsolePrint(ErrorText.c_str());
		BOOM;
		return false;
	}

	if (
		GraphicDevice::Inst()->GetDXDevice()->CreatePixelShader
		(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&pixelShader
		)
		)
	{
		BOOM;
		return false;
	}

	return true;
}

void PxlShader::Update()
{
	if (nullptr != pixelShader)
	{
		GraphicDevice::Inst()->GetDXContext()->PSSetShader(pixelShader, nullptr, 0);
	}
}
