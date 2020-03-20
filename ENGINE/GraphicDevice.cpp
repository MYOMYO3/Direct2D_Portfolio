#include "GraphicDevice.h"
#include <MyWindow.h>


#pragma region MGR

//std::map<std::wstring, My_Ptr<GraphicDevice>> GraphicDevice::g_DeviceMap;
GraphicDevice* GraphicDevice::m_Inst = nullptr;
bool GraphicDevice::pathInit = false;


//My_Ptr<GraphicDevice> GraphicDevice::CreateDevice(const wchar_t* _WindowName)
//{
//	My_Ptr<Window> findWindow = Window::FindMyWindow(_WindowName);
//
//	if (nullptr == findWindow)
//	{
//		BOOM;
//	}
//
//	My_Ptr<GraphicDevice> newDevice = new GraphicDevice();
//
//	newDevice->Init(findWindow);
//
//	if (0 == g_DeviceMap.size())
//	{
//		m_Inst = newDevice;
//	}
//	newDevice->BaseResInit();
//	newDevice->baseInit = true;
//
//
//	g_DeviceMap.insert(std::map<std::wstring, My_Ptr<GraphicDevice>>::value_type(_WindowName, newDevice));
//
//	//return nullptr;
//	return newDevice;
//}


#pragma endregion


#pragma region MEMBER

GraphicDevice::GraphicDevice(): device(nullptr), context(nullptr), swapChain(nullptr), 
								depthStencilView(nullptr), texture2D(nullptr), backBufferView(nullptr), baseInit(false)
{

}


GraphicDevice::~GraphicDevice()
{
	targetWindow = nullptr;

	if (nullptr != texture2D)			{ texture2D			->Release();	texture2D			= nullptr; };
	if (nullptr != depthStencilView)	{ depthStencilView	->Release();	depthStencilView	= nullptr; };
	if (nullptr != backBufferView)		{ backBufferView	->Release();	backBufferView		= nullptr; };
	if (nullptr != swapChain)			{ swapChain			->Release();	swapChain			= nullptr; };
	if (nullptr != context)				{ context			->Release();	context				= nullptr; };
	if (nullptr != device)				{ device			->Release();	device				= nullptr; };
}

void GraphicDevice::MainReset()
{
	context->VSSetShader(nullptr, nullptr, 0);
	context->HSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->CSSetShader(nullptr, nullptr, 0);
	context->DSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->OMSetDepthStencilState(nullptr, 0);
}

void GraphicDevice::Init(Window* _TargetWindow)
{
	int flag = 0;

#ifdef  _DEBUG
	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG
	targetWindow = _TargetWindow;

	D3D_FEATURE_LEVEL eLv = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;


	backColor = { 4.0f/ 255.0f, 104.0f / 255.0f, 216.0f / 255.0f, 1.0f }; 

	
	//QueryInterface(__uuidof(IDXGIDevice), (void**)&giDevice);
	//giDevice->GetAdapter(&pAdapter);
	
	iAdapter = 0;
	if (S_OK != CreateDXGIFactory1(__uuidof(IDXGIFactory), (void**)&factory))
	{		
		return;
	}

	//IDXGIDevice::GetAdapter(&pAdapter);
	if (S_OK != factory->EnumAdapters(iAdapter, &pAdapter))
	{		
		return;
	}
	pAdapter->GetDesc(&adapterDesc);
	pAdapter->EnumOutputs(iAdapter, &pOutput);
	pOutput	->GetDesc(&outDesc);
	
	
	HRESULT check;

	check = D3D11CreateDevice
	(
		nullptr,	//����̽� ���鶧 �ΰ������� �ֳ���? nullptr
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,	//�׷���ī�尡 � ��ݿ� ���Ѱ��ΰ� -> �ϵ����
		nullptr,
		flag,
		nullptr,
		0,
		D3D11_SDK_VERSION, //SDK����
		&device,
		&eLv,
		&context
	);

	//check = D3D11CreateDevice
	//(
	//	pAdapter,	//����̽� ���鶧 �ΰ������� �ֳ���? nullptr
	//	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,	//�׷���ī�尡 � ��ݿ� ���Ѱ��ΰ� -> �ϵ����
	//	nullptr,
	//	flag,
	//	nullptr,
	//	0,
	//	D3D11_SDK_VERSION, //SDK����
	//	&device,
	//	&eLv,
	//	&context
	//);

	if (S_OK != check) { BOOM; return; }

	//�̰� ���� ������� ó���ϴ� ���̱� ������ ���� ������ �Ǵ� ������
	//DXGI_FORMAT_R8G8B8A8_UNORM
	//device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAA_LV);

	////����ü���� �����.......
	//check = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAA_LV);
	//if (S_OK != check) { BOOM; return; }


	multisampleLevel	= 4;
	multisampleQuality	= 0;

	D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	check = device->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, multisampleLevel, &multisampleQuality);
	if (S_OK != check)
	{
		multisampleLevel = 1;
		multisampleQuality = 0;
		check = device->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, multisampleLevel, &multisampleQuality);
		return;
	}
	multisampleLevel = 1;
	multisampleQuality = 0;

	// ����ü���� �����.
	// ���� ������ 
	if (false == CreateSwapChain())
	{
		BOOM;
	}

	if (false == CreateDepthStencilView())
	{
		BOOM;
	}

	if (false == CreateViewPort())
	{
		BOOM;
	}

	if (nullptr == m_Inst)
	{
		m_Inst = this;
		device = this->GetDXDevice();
		context = this->GetDXContext();
	}

	BaseResInit();
}

////PUBLIC
void GraphicDevice::ClearTarget()
{
	if (nullptr != context)
	{
		context->ClearRenderTargetView(backBufferView, backColor.Arr);
		context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}
void GraphicDevice::Present()
{
	if (nullptr != swapChain)
	{
		swapChain->Present(0, 0);
	}
}

////PRIVATE
bool GraphicDevice::CreateSwapChain()
{
	

	//DESC �ܾ� ������ ��ũ���� ����
	DXGI_SWAP_CHAIN_DESC SCInfo;

	SCInfo.BufferDesc.Width		= targetWindow->GetWindowSize().UINT_X();
	SCInfo.BufferDesc.Height	= targetWindow->GetWindowSize().UINT_Y();

	//������� �ִ��ػ󵵸� ���ü� �ִ�.
	//������� �츣��(�ֻ���)�� ���ü� �ִ�.

	//���� �и�
	SCInfo.BufferDesc.RefreshRate.Numerator		= 144;
	SCInfo.BufferDesc.RefreshRate.Denominator	= 1;

	SCInfo.BufferDesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
	SCInfo.BufferDesc.ScanlineOrdering	= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SCInfo.BufferDesc.Scaling			= DXGI_MODE_SCALING_UNSPECIFIED;

	//������� �뵵
	//ȭ�鿡 ����ϴ� �뵵�� ���δ�
	SCInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//������� ����
	//��Ƽ���ø� ����Ƽ
	//0 �˾Ƽ�
	//SCInfo.SampleDesc.Count = m_ML;
	SCInfo.SampleDesc.Count = multisampleLevel;
	SCInfo.SampleDesc.Quality = multisampleQuality;

	// ������۸��� ����ѵ�.
// 2���� �̹����� 
	SCInfo.OutputWindow = targetWindow->GetHWnd();
	// ���۰��� 1 ~ 
	SCInfo.BufferCount = 2;

	//0  -> ȭ�鿡 ������ �ִ�.
	//1 -> �׷����� �ִ�. -> �� �׷�����.
	//���� ������ �������
	//2���� �׸��� �׸��� �����Ҷ� ����� ���α׸���. -> �� �׷����� -> ������
	SCInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//swap chain ����Ʈ

	//Ǯ��ũ�� �ΰ���
	SCInfo.Windowed =! targetWindow->IsFull();
	SCInfo.Flags = 0;
	DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED;

	//������ ���õȰŰ�
	//���� ����� ���� �ؾ��Ѵ�.
	//�׷��� ���̷�Ʈ�� ����ü���� ����� ���ؼ� �� ������ ������ ���ľ��Ѵ�.

	// ���̷�Ʈ 11���ʹ� ���̵��� �������ٴ� ������
	//com��ü����̶�� ���� ����ؼ� ó���ϰ� ������

	//m_pDevice->createsw
	//�̳༮���� �ܼ��� ���� �Ҵ��ϰ� �����Ǵ� �༮�� �ƴϰ�
	//���ҿ��� ���� �޸� ������Ŀ� ���� ���� �����ǰ� �ִ�.
	// �׷���ī�忡 ������ ��û�ϰų� �޸𸮸� �Ҵ��ϴ� ��Ŀ� ���� �������̽���
	// new Texture();
	// �̳༮���� ���ؼ��� �׷���ī�忡 ��û�ض�.
	// ID3D11Device* m_pDevice

	IDXGIDevice*	pidxDevice	= nullptr;
	IDXGIAdapter*	pIdxAdapter = nullptr;
	IDXGIFactory*	pIdxFactory = nullptr;
	// �̰� ������ �ʰ��� 
	// ������� �س���.
	// �׷��� ī����� ���

	device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pidxDevice);
	if (nullptr == pidxDevice)
	{
		BOOM;
		return false;
	}

	//GUID�� ���ؼ� ������ ����� ����.
	pidxDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pIdxAdapter);
	if (nullptr == pIdxAdapter)
	{
		BOOM;
		return false;
	}

	pIdxAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pIdxFactory);
	if (nullptr == pIdxFactory)
	{
		BOOM;
		return false;
	}

	if (S_OK != pIdxFactory->CreateSwapChain(device, &SCInfo, &swapChain))
	{
		BOOM;
		return false;
	}

	pIdxFactory	->Release();
	pIdxAdapter	->Release();
	pidxDevice	->Release();

	return true;
}

bool GraphicDevice::CreateDepthStencilView()
{
	ID3D11Texture2D* backBufferTex = nullptr;

	//�ڵ����� �ؽ��� �ϳ��� ��������ֱ� ������ �̰� ���ü� �ִ�.
	if (S_OK != swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTex))
	{
		BOOM;
		return false;
	}

	//���̷�Ʈ�� view��� ǥ���� ��ü����
	//�ؽ��Ŀ� ���� ������ ó�������� ����Ҽ� �ִ� �������̽��̴�.
	//������� ���̿� �����ϰų� ��ɳ����� �ִ� ���� ��ü�� �������
	//���߿� ����ۿ� ��� ����� ������ �̳༮�� ���ؼ� ������
	
	if (S_OK != device->CreateRenderTargetView(backBufferTex, 0, &backBufferView))
	{
		BOOM;
		return false;
	}

	if (nullptr != backBufferTex)
	{
		backBufferTex->Release();
		backBufferTex = nullptr;
	}

	D3D11_TEXTURE2D_DESC textureDesc = {};

	textureDesc.ArraySize = 1;
	textureDesc.Width = targetWindow->GetWindowSize().UINT_X();
	textureDesc.Height = targetWindow->GetWindowSize().UINT_Y();

	//�ſ� ����ų�
	//���� ��Ÿ�� �ϰ�ʹٰų�
	//ȭ���� ��� �ȼ��� ���ٽ� ���� 4�γ༮�� ���ҰԿ�
	//3����Ʈ�� ���� ������ ����ϰ� �ڿ� 8��Ʈ�� 0~255 ���ٽ� ������ ����Ѵ�.

	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.MipLevels = 1; // �� �����ؾ� �Ѵ�.
	// �޸� ���� �ɼ�
	// D3D11_USAGE_DEFAULT�� �׷���ī�忡�� �����ض�.
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	// �ؽ�ó�� �뵵�� ����?
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	device->CreateTexture2D(&textureDesc, 0, &texture2D);

	if (nullptr == texture2D)
	{
		BOOM;
		return false;
	}

	device->CreateDepthStencilView(texture2D, 0, &depthStencilView);

	if (nullptr == depthStencilView)
	{
		BOOM;
		return false;
	}

	// D3D11_DEPTH_STENCIL_DESC TD;
	// m_pContext->OMSetDepthStencilState(TD, 1);

	return true;



}

bool GraphicDevice::CreateViewPort()
{
	viewPortInfo.TopLeftX = 0;
	viewPortInfo.TopLeftY = 0;

	viewPortInfo.Width = targetWindow->GetWindowSize().x;
	viewPortInfo.Height = targetWindow->GetWindowSize().y;
	viewPortInfo.MinDepth = 0.0f;
	viewPortInfo.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewPortInfo);

	return true;
}

#pragma endregion


void GraphicDevice::RenderTargetSetting()
{
	if (nullptr != context && nullptr != depthStencilView)
	{
		//���� ���۴� �׷��� ��ü�� ������ ��� ����� ����.
		//���� �� ����Ÿ�ٰ� �� ���̹��۸� ����ؼ�
		//�׷����� ����� ����� ������ �����ϰڽ��ϴ�.

		context->OMSetRenderTargets(1, &backBufferView, depthStencilView);
	}
}

void GraphicDevice::ViewPortSetting()
{
	if (nullptr != context)
	{
		context->RSSetViewports(1, &viewPortInfo);
	}
}



