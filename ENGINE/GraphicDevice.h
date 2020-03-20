#pragma once

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\_BASED32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\_BASER32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\_BASED64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\_BASER64.lib")
#endif
#endif

#include <Maths.h>

//������ 10���ʹ� ������ �� ��ü�� ���������� ���̷�Ʈ�� ���̰� �ֱ⶧����
//������ ��� c++������  stdlib�������� �� include ���Ա��� �Ǿ��ִ�.

#define D3D2

//#include <DirectXMath.h>
#include <d3dtypes.h>
#include <d3d11_4.h>

#include <d3dcompiler.h> //���̴��� �����Ϸ��ϴµ� ���Ǵ� ���
#include <MyWindow.h>
#include <map>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dxgi")



//�׷��� ī���� ����� ����ϱ� ���� ���̺귯���� D3DX �� ����� ��Ƶ� Ŭ����

class Window;
class GraphicDevice : public ControlBlock
{
private:
	//static GraphicDevice* mainDevice;	
	static GraphicDevice* m_Inst;
	static bool pathInit;
	//static ID3D11Device* pMainDevice;

public:
	static GraphicDevice* Inst()
	{
		return m_Inst;
	}
	
	//My_Ptr<GraphicDevice> CreateDevice(const wchar_t* _WindowName);

/////////MEMBER
private:
	UINT				iAdapter;
	IDXGIFactory*		factory;	
	IDXGIAdapter*		pAdapter;
	IDXGIOutput*		pOutput;
	DXGI_ADAPTER_DESC	adapterDesc;
	DXGI_OUTPUT_DESC	outDesc;
	IDXGIDevice*		giDevice;

private:
	Window* targetWindow;
	UINT MSAA_LV;	//��Ƽ ���ø� ����
	//�׷���ī�带 ���̷�Ʈ�� ���α׷����ϴ°Ϳ����� ������ �Ʒ��� �ΰ��� �����͸� ���ؼ� �Ѵ�.
	ID3D11Device*			device;	//�׷���ī�忡 ���� ��� �ڿ��� ���� ������ ���
	ID3D11DeviceContext*	context;	//�׷���ī���� ��� ���꿡 ���� ������ ����Ѵ�.	
	IDXGISwapChain*			swapChain; //IDXGISwapChain�� �������̽��� �ϳ� �̻��� ���� ǥ�� ��¿� ������ ���� ������ �� �����͸� �����Ѵ�.
	ID3D11RenderTargetView* backBufferView;
	ID3D11DepthStencilView* depthStencilView;	//���� ���� ������ ���������ο� �����Ѵ�.
	ID3D11Texture2D*		texture2D;	//2D �ؽ�ó �������̽��� ����ȭ �� �޸� �� �ؼ� �����͸� �����մϴ�.
		
	Vector4					backColor;
	D3D11_VIEWPORT			viewPortInfo;	//����Ʈ ��Ŀ� ����
	
	UINT multisampleLevel;
	UINT multisampleQuality;
	
	bool baseInit;
	void BaseResInit();

	void DeviceStateInit();
	void MeshInfoInit();
	void ShaderInfoInit();

public:
	void MainReset();

	ID3D11Device* GetDXDevice()
	{
		return device;
	}
	ID3D11DeviceContext* GetDXContext()
	{
		return context;
	}

public:
	void Init(Window* _TargetWindow);

	void ClearTarget();
	void Present();

private:
	//���̷�Ʈ x������ �츮�� ���� �����ʿ䰡 ���� ȭ�� ���ŽŽ����� �������ش�.
	bool CreateSwapChain();
	bool CreateDepthStencilView();
	bool CreateViewPort();

public:
	void RenderTargetSetting();
	void ViewPortSetting();

public:
	GraphicDevice();
	~GraphicDevice();
};

