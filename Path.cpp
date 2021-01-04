#include "stdafx.h"
#include "Path.h"
#include <string.h>
#include "String.h"
//PATH(경로)는 특정한 파일이 있는 위치를 나타내는 주소이다, Windows에는 PATH라는 이름의 환경변수가 있다.
bool Path::ExistFile(string path)//지정된 파일이 있는지 확인한다.
{
	return ExistFile(String::ToWString(path));
}
//wstring = 한글 문자열을 담을수 있는 통로, c언어 = w_char 로 표현한다.
bool Path::ExistFile(wstring path)
{//GetFileAttributes() = 이 함수는 파일이나 폴더의 속성을 알아보는 용도이다.(읽기전용,쓰기전용 등등), 파일이 없는경우 INVALID_FILE_ATTRIBUTES(-1)을 리턴한다.
	DWORD fileValue = GetFileAttributes(path.c_str()); // c_str = ipfilename 이다. (IpFileName = 대상파일경로 이름을 넣으면된다)

	return fileValue < 0xFFFFFFFF; // 0xFFFFFFFF = 16진수의값이다. 2진수로 변환하면 "-1"의값을 가진다.
}// 즉 -1보다 작을때 값을 리턴한다.

bool Path::ExistDirectory(string path) 
{//ExistDirectory = 지정된 경로가 디스크에 있는 기존 디렉터리를 참조하는지 확인하는것.
	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(wstring path)
{//위와 같다. 다만 String이 아닌 wstring을 사용함으로써, 한글문자열을 담을수있는 
	DWORD attribute = GetFileAttributes(path.c_str()); //DWORD = unsigned long 이고, 4바이트를 지닌 자료형이다.
 //BOOL = int이고, 4바이트를 지닌 자료형이다. bool = char,1byte   //WORD = unsigned short 이고, 2바이트를 지닌 자료형이다.
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && //GetFileAttributes 속성이, INVALID_FILE_ATTRIBUTES && 와 같지않은지 비교한다.
		(attribute & FILE_ATTRIBUTE_DIRECTORY)); // 속성 과 폴더

	return temp == TRUE; // 매개변수 템프가 작동되면 실행되며 리턴된다.
}

string Path::Combine(string path1, string path2) // 두 문자열을 한 경로(string)로 결합한다.
{
	return path1 + path2;  // 두 문자열을 하나로 합친 하나의 경로를 리턴한다.
}

wstring Path::Combine(wstring path1, wstring path2) // 두 문자열을 한 경로(wstring)로 결합한다.
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths) //문자열(string)을 저장하는 vector를 하나의 경로로 결합한다.
{
	string temp = ""; // 가상함수 temp 를 " " 로 정의.
	for (string path : paths)
		temp += path; // path = temp + path의 값을 말한다.

	return temp; // " " 값을 리턴한다.
}

wstring Path::Combine(vector<wstring> paths) // 문자열(string)을 저장하는 vector를 하나의 경로로 결합한다.
{
	wstring temp = L""; //와이드 문자열에 상수를 작성하기위해선 문자 상수 앞에 L을 붙인다. wstring은 와이드 문자열이기때문에 문자앞에 L을 붙인다.
	for (wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(string path) // 지정된 경로는 string path 이다.
{//GetDirectoryName 함수를 사용하면 지정된 경로에 디렉터리 정보를 반환한다.
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{//GetExtension 함수는 지정된 경로 문자열의 확장명(마침표 "." 포함) 을 반환한다. 
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

string Path::GetFileName(string path) 
{//GetFileName 함수는 지정된 경로 문자열에서 파일 이름과,확장명을 반환한다.
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

string Path::GetFileNameWithoutExtension(string path)
{//GetFileNameWithoutExtension 함수는 확장명 없이 지정된 경로 문자열의 "파일 이름"만 반환한다.
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

//필터링 = 원하지않는것을 걸러내는것.
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";  //Image
const WCHAR* Path::BinModelFilter = L"Binary Model\0*.model"; //BinModel 
const WCHAR* Path::FbxModelFilter = L"Fbx Model\0*.fbx;*.obj\0"; //FbxModel
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl"; //ShaderFileter = 필터링되는 객체에 셰이더를 실행하여 필터를 적용시킨다. 필터링된 객체는 셰이더에 대한 입력으로 사용되고 이 셰이더 출력은 필터 결과가 된다.

void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{//OpenFileDialog() = 사용자가 파일을 열도록 요청하는 표준 대화 상자를 표시. 이 클래스는 상속 될 수 없다.
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"불러오기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{//SaveFileDialog() = 파일 저장대화 상자를 표시하고 사용자가 선택한 파일을 저장하는 메서드를 호출한다.
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

//path : ../Temp/
//filter : *.txt
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";

					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else
			{
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
		} while (FindNextFile(handle, &findData));

		FindClose(handle);
	}
}

void Path::CreateFolder(string path)
{//CreateFolder() = 폴더생성
	CreateFolder(String::ToWString(path));
}

void Path::CreateFolder(wstring path)
{
	if (ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), NULL);
}

void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWString(path));
}

void Path::CreateFolders(wstring path)
{
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(&folders, path, L"/");

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";

		CreateFolder(temp);
	}
}
