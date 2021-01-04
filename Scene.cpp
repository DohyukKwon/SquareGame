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


//�������� 


//----����������������----
//IA = Input Assemply
//VS = ������ó���ϴ´ܰ� (3D)  ���⼭ wvp ó��.
//PS = �ȼ�(2D)
//RS = ���������� ������� ������ ����
//OM = Output merge = �����γ������°� ��ġ�´ܰ�
//DSV
//RTV , ������
//GS
//�׼����̼�
//������������ �˾ƺ���
//�޼���ǥ��

//Ű���� �м�
//�����Ѱźм�

// ������ �簢���� �ϳ� ���� �������� �簢�� ���� �� ���� �ε����� ��������ϴ°� �����

//cpu,gpu ������žȵǰ�, �������ؼ�(�������)�����ؼ� �����Ѵ�. ��������ũ��� �ý��ۿü�������� �ٸ���.
//cpu->������ gpu->�ܼ��뵿�� �������ϸ����ϴ�. �̰ɰ����ϰ��ϴ°� ���̴�.
//gpu���� �����ִ� ��� �ڷ����� float�̴�. �׶���������ȸ��� double�� ����Ѵ�.
//gpu�� �����ϴ°� ���̴�.
//cpu = ��ü���� 
//gpu = �Լ����� (�Լ�ȭ ����ȭ ���α׷� . ���ý���).. �츮���˰� �Լ������̶��ٸ���.
//shader�� �𸣸� ��ó�����ȵȴ�. �Ҽ������� �ʹ�������. 