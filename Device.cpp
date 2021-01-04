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

void InitWindow(HINSTANCE hInstance, int ShowWnd) //Window 창 띄우는곳
{
	//Register Class
	{
		WNDCLASSEX wndClass; //EX = 확장.
		wndClass.cbSize = sizeof(WNDCLASSEX); // 윈도우클래스 크기
		wndClass.style = CS_HREDRAW | CS_VREDRAW; // 수직 및 수직으로 그려라.
		wndClass.lpfnWndProc = WndProc; // proc은 메세지가 들어오면 처리해주겠다.
		wndClass.cbClsExtra = NULL; // Extra 
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = hInstance; //현재프로그램창에 식별자 알려준다.
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wndClass.lpszMenuName = NULL; //imgui사용함.
		wndClass.lpszClassName = Title.c_str(); // 타이틀이름똑같이해주는거
		wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //스몰아이콘.

		WORD check = RegisterClassEx(&wndClass);
		assert(check != 0);  //assert =  조건이 트루면 통과, false면 해당위치에서 에러찾을수있다.
	}

	//Create Handle
	{
		Hwnd = CreateWindowEx
		(
			NULL,
			Title.c_str(),
			Title.c_str(),
			WS_OVERLAPPEDWINDOW, //윈도우 겹치게 가능하게해주는것
			CW_USEDEFAULT, CW_USEDEFAULT, // 최초로 창을띄웠을때 x,y
			Width, Height,
			NULL,
			NULL,
			hInstance,
			NULL
		);
		assert(Hwnd != NULL);
	}

	RECT rect = { 0,0,(LONG)Width, (LONG)Height }; //WIN API 는 왼쪽위부터 오른쪽아래로 그려진다 
	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2; //실제그려지는 화면의 중심잡기
	UINT centerY = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE); //BOOL형 , WindowAPI는 전부 BOOL형으로 리턴한다. , 1보다크면 트루 0이하면 false다.
	MoveWindow
	(
		Hwnd,
		centerX, centerY,
		rect.right - rect.left, rect.bottom - rect.top,
		TRUE
	);
	 //WinAPI 를이용한 게임은 던파밖에없다.

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
	if (ImGui::WndProc((UINT*)hwnd, msg, wParam, lParam))// ImGui UI움직일수 있게해준다.
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


