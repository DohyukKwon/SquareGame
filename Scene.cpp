#include "stdafx.h"
#include "Device.h"
#include <math.h>
#include "Draws/Rect.h"

Math math;
Rect* rect;
Rect* rect2;
vector<Rect*> enemies;

void InitScene()
{
	rect = new Rect(L"../_Shaders/005_WVP.fx");
	rect->Position(50, 50);
	rect->Scale(100, 100);
	rect->Color(1, 1, 1);

	rect2 = new Rect
	(
		L"../_Shaders/005_WVP.fx",
		D3DXVECTOR2(500, 500),
		D3DXVECTOR2(100, 100),
		D3DXCOLOR(0, 0, 1, 1)
	);
}

void DestroyScene()
{
	SAFE_DELETE(rect);
	SAFE_DELETE(rect2);
	for (int i = 0; i < enemies.size(); i++)
	{
		SAFE_DELETE(enemies[i]);
	}
}


D3DXMATRIX V, P;
void Update()
{
	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	rect->ViewProjection(V, P);
	rect2->ViewProjection(V, P);

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->ViewProjection(V, P);
	}

	rect->Update();
	rect2->Update();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (rect->Position().x - rect->Scale().x / 2 <= enemies[i]->Position().x + enemies[i]->Scale().x / 2
			&& rect->Position().x + rect->Scale().x / 2 >= enemies[i]->Position().x - enemies[i]->Scale().x / 2
			&& rect->Position().y - rect->Scale().y / 2 <= enemies[i]->Position().y + enemies[i]->Scale().y / 2
			&& rect->Position().y + rect->Scale().y / 2 >= enemies[i]->Position().y - enemies[i]->Scale().y / 2)
		{
			rect->Scale(sqrt(rect->Scale().x * rect->Scale().y + enemies[i]->Scale().x*enemies[i]->Scale().y), sqrt(rect->Scale().x * rect->Scale().y + enemies[i]->Scale().x*enemies[i]->Scale().y));
			rect->Color((rect->Color().r + enemies[i]->Color().r) / 2, (rect->Color().g + enemies[i]->Color().g) / 2, (rect->Color().b + enemies[i]->Color().b) / 2);
			enemies[i]->Position(-1000, -1000);
		}

	}
	if (rect->Scale().x > 500)
		ImGui::EndPopup();


}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float *)bgColor);
	{
		rect->SlidePosition();

		if (ImGui::Button("Enemy", ImVec2(100, 20)))
		{
			bool a = 0;


			enemies.push_back(rect);
			int scaleX = math.Random(0, 200);
			int scaleY = math.Random(0, 100);
			int x = math.Random(0, 1024 - scaleX);
			int y = math.Random(0, 768 - scaleY);
			enemies.back() = new Rect
			(
				L"../_Shaders/005_WVP.fx",
				D3DXVECTOR2(x, y),
				D3DXVECTOR2(scaleX, scaleY),
				D3DXCOLOR(math.Random(0.1f, 1.0f), math.Random(0.1f, 1.0f), math.Random(0.1f, 1.0f), 1)
			);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Render();

		}
		rect->Render();


	}
	ImGui::Render();
	SwapChain->Present(0, 0);

}


//선형보관 


//----랜더링파이프라인----
//IA = Input Assemply
//VS = 정점을처리하는단계 (3D)  여기서 wvp 처리.
//PS = 픽셀(2D)
//RS = 정점정보를 기반으로 정보룰 보관
//OM = Output merge = 밖으로내보내는걸 합치는단계
//DSV
//RTV , 빽버퍼
//GS
//테셀레이션
//랜더링파이프 알아보기
//왼손좌표계

//키보드 분석
//오늘한거분석

// 움직일 사각형을 하나 만들어서 여러개의 사각형 색상 및 생성 부딪히면 사라지게하는거 만들기

//cpu,gpu 직접통신안되고, 램을통해서(저장공간)을통해서 교류한다. 포인터의크기는 시스템운영체제에따라 다르다.
//cpu->전문가 gpu->단순노동자 라고생각하면편하다. 이걸가능하게하는게 쉐이더.
//gpu에서 쓸수있는 모든 자료형은 float이다. 그란투리스모회사는 double을 사용한다.
//gpu를 제어하는게 쉐이더.
//cpu = 객체지향 
//gpu = 함수지향 (함수화 병렬화 프로그램 . 동시실행).. 우리가알고 함수지향이랑다르다.
//shader를 모르면 후처리가안된다. 할수있지만 너무느리다. 