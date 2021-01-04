#pragma once

#include <Windows.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <random>
using namespace std;

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dX10.h>
#include <d3dx10math.h>
#include <d3dx11effect.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "effects11d.lib")
#pragma comment(lib, "d3dcompiler.lib")

//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "imgui.lib")

#include "Renders/Shader.h"
#include "Systems/Keyboard.h"
#include "Draws/Rect.h"


#include "Utilities/Math.h"
#include "Utilities/Path.h"
#include "Utilities/String.h"


#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p){ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p){ delete [] (p); (p) = NULL; } }


const UINT Width = 1024;
const UINT Height = 768;

extern HWND Hwnd;
extern wstring Title;

extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern Keyboard* Key;


// Path, Math, String Ŭ���� �м�(�ּ�üũ �� ������ �� ī�信 �ø���) 29�ϱ���.
// ImGui ���� ���δ� ���˾ƺ���!

//�������� = ��� 
//����׸�� = �����ڸ�� 
//����ƽ, ����Լ�, ��üȭ (�߿�)�ڡڡڡڡڡ� , ����ƽ���Ѿ �̱����̶�� �ִ�.
//string �� ������ �Լ� ã�ƺ���
//������ �� �� .. *int, int*, &int, int& 
///////////////////////////////////////////
//WVP = World v p 
//������ ��ü�� ���ε��ο��������ʴ´�. Wolrd�� �ְ� World�� �����ϲ���.
//�޼���ǥ�� = �޼��� ���������θ��� (�ð����) - ��켱.
//��������ǥ�� - �������� �޼��� �θ��� (�ݽð����) �׳� �̷������� ���ϰԻ����Ҷ�. - ���켱.
//������� = ��,��,��,�� (��������) ���� �ٲ����ʴ°� ex. ��ħ��
//������(���ð���,��������) = �����ؿ����� ��,��,��,���� �ٲ�°� 
//View = �츮�� �ٶ󺸴� ����. ���� = 4x4 ����̴�, ������ �׻� ��ķ� ǥ�������ϴ�. �޼���ǥ������ ��켱�����ϰ�, ��������ǥ�� ���켱�����Ѵ�.
//World = 1024x768 
//dx9 ������ ��켱�̴�.
//dx10 ���ʹ� ���켱�̴�.
//OpenGL �� ���켱�̰� ���̷�Ʈ�ϰ� �ݴ��̴�.
//rowmanage = ��켱 �ɼǲ��� ���켱�̴�.
//�߽����� ũ��. �߽����߿� �߽����� World�� �߽�.
//ũ�� �ø��� �̵��ϴ°Ŷ� �̵��ϰ� �ø��Ŷ��� �ƿ��ٸ���.
//�̵��ϰ� �����°Ŷ� ������ �̵��ϴ°Ŷ��� �ƿ��ٸ���.

//Unity S,R,T �̴�.  OpenGL,Unreal = T,R,S



//---------------------------------------
//imgui.master ���� ��ư������ ��������ġ�� �����ѻ���� ������ũ��� �簢��
//math�Լ���  rand �� ��ư�������� ȭ������ȿ��� �߰��ϰ�
//Player�� �浹�ϸ� ���� �������� �÷��̾�� �� ����� ũ�⸸ŭ����.
//����ũ�Ⱑ �Ѿ�� ��������



