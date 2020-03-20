#pragma once
#include "Resources.h"



class Rasterizer : public Resources
{
private:
	// Unmap ���� ������.
// ���Ƽ� ���ִ� ����ȭ ���
	D3D11_RASTERIZER_DESC		desc;
	ID3D11RasterizerState*		state; // ���ؽ�

public:
	bool Create();
	bool Create(const D3D11_RASTERIZER_DESC& _Desc);
	void Update();


public:
	Rasterizer();
	~Rasterizer();
};

