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


// Path, Math, String 클래스 분석(주석체크 및 공부한 후 카페에 올리기) 29일까지.
// ImGui 많이 쓰인다 꼭알아보기!

//릴리즈모드 = 출시 
//디버그모드 = 개발자모드 
//스태틱, 멤버함수, 객체화 (중요)★★★★★★ , 스태틱을넘어서 싱글턴이라고 있다.
//string 에 유용한 함수 찾아보기
//포인터 및 값 .. *int, int*, &int, int& 
///////////////////////////////////////////
//WVP = World v p 
//앞으로 물체를 따로따로움직이지않는다. Wolrd에 넣고 World를 움직일꺼다.
//왼손자표계 = 왼손이 오른손을두른다 (시계방향) - 행우선.
//오른손좌표계 - 오른손이 왼손을 두른다 (반시계방향) 그냥 이론적으로 편하게생각할때. - 열우선.
//절대공간 = 동,서,남,북 (지구기준) 절대 바뀌지않는것 ex. 나침반
//상대공간(로컬공간,지역공간) = 내기준에서는 동,서,남,북이 바뀌는것 
//View = 우리가 바라보는 공간. 공간 = 4x4 행렬이다, 공간은 항상 행렬로 표현가능하다. 왼손좌표를쓸땐 행우선으로하고, 오른손좌표는 열우선으로한다.
//World = 1024x768 
//dx9 까지는 행우선이다.
//dx10 부터는 열우선이다.
//OpenGL 은 열우선이고 다이렉트하고 반대이다.
//rowmanage = 행우선 옵션끄면 열우선이다.
//중심점의 크기. 중심점중요 중심점은 World의 중심.
//크기 늘리고 이동하는거랑 이동하고 늘린거랑은 아예다르다.
//이동하고 돌리는거랑 돌리고 이동하는거랑은 아예다르다.

//Unity S,R,T 이다.  OpenGL,Unreal = T,R,S



//---------------------------------------
//imgui.master 보면 버튼누르면 랜덤한위치에 랜덤한색깔로 랜덤한크기로 사각형
//math함수에  rand 로 버튼을누르면 화면범위안에서 추가하고
//Player는 충돌하면 상대는 없어지고 플레이어는 몹 색상및 크기만큼증가.
//일정크기가 넘어가면 게임종료



