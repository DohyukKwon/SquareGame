#include "stdafx.h"
#include "Device.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitWindow(hInstance, nShowCmd);
	InitDirect3D(hInstance);

	Running();

	Destroy();

	return 0;
}


HWND Hwnd = NULL;
wstring Title = L"Draw Sprite";

IDXGISwapChain* SwapChain;
ID3D11Device* Device;
ID3D11DeviceContext* DeviceContext;
ID3D11RenderTargetView* RTV;

Keyboard* Key;

void InitWindow(HINSTANCE hInstance, int ShowWnd) //Window â ���°�
{
	//Register Class
	{
		WNDCLASSEX wndClass; //EX = Ȯ��.
		wndClass.cbSize = sizeof(WNDCLASSEX); // ������Ŭ���� ũ��
		wndClass.style = CS_HREDRAW | CS_VREDRAW; // ���� �� �������� �׷���.
		wndClass.lpfnWndProc = WndProc; // proc�� �޼����� ������ ó�����ְڴ�.
		wndClass.cbClsExtra = NULL; // Extra 
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = hInstance; //�������α׷�â�� �ĺ��� �˷��ش�.
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wndClass.lpszMenuName = NULL; //imgui�����.
		wndClass.lpszClassName = Title.c_str(); // Ÿ��Ʋ�̸��Ȱ������ִ°�
		wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //����������.

		WORD check = RegisterClassEx(&wndClass);
		assert(check != 0);  //assert =  ������ Ʈ��� ���, false�� �ش���ġ���� ����ã�����ִ�.
	}

	//Create Handle
	{
		Hwnd = CreateWindowEx
		(
			NULL,
			Title.c_str(),
			Title.c_str(),
			WS_OVERLAPPEDWINDOW, //������ ��ġ�� �����ϰ����ִ°�
			CW_USEDEFAULT, CW_USEDEFAULT, // ���ʷ� â��������� x,y
			Width, Height,
			NULL,
			NULL,
			hInstance,
			NULL
		);
		assert(Hwnd != NULL);
	}

	RECT rect = { 0,0,(LONG)Width, (LONG)Height }; //WIN API �� ���������� �����ʾƷ��� �׷����� 
	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2; //�����׷����� ȭ���� �߽����
	UINT centerY = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE); //BOOL�� , WindowAPI�� ���� BOOL������ �����Ѵ�. , 1����ũ�� Ʈ�� 0���ϸ� false��.
	MoveWindow
	(
		Hwnd,
		centerX, centerY,
		rect.right - rect.left, rect.bottom - rect.top,
		TRUE
	);
	 //WinAPI ���̿��� ������ ���Ĺۿ�����.

	ShowWindow(Hwnd, ShowWnd);
	UpdateWindow(Hwnd);
}

void InitDirect3D(HINSTANCE hInstance)
{
	//Create Device and DeviceContext, SwapChain
	{
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = Width;
		bufferDesc.Height = Height;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferDesc = bufferDesc;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = Hwnd;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &desc, &SwapChain, &Device, NULL, &DeviceContext
		);
		assert(SUCCEEDED(hr));
	}

	//Create BackBuffer
	{
		HRESULT hr;

		ID3D11Texture2D* BackBuffer;
		hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		assert(SUCCEEDED(hr));

		hr = Device->CreateRenderTargetView(BackBuffer, NULL, &RTV);
		assert(SUCCEEDED(hr));
		BackBuffer->Release();

		DeviceContext->OMSetRenderTargets(1, &RTV, NULL);
	}

	//Create Viewport
	{
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = Width;
		viewport.Height = Height;

		DeviceContext->RSSetViewports(1, &viewport);
	}
}

void Destroy()
{
	SwapChain->Release();
	Device->Release();
	DeviceContext->Release();
	RTV->Release();
}

WPARAM Running()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	ImGui::Create(Hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();

	Key = new Keyboard();

	InitScene();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			Update();
			ImGui::Update();

			Render();
		}
	}
	DestroyScene();

	delete Key;
	ImGui::Delete();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc((UINT*)hwnd, msg, wParam, lParam))// ImGui UI�����ϼ� �ְ����ش�.
	return true;

	switch (msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) 
			{
				DestroyWindow(hwnd);
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


