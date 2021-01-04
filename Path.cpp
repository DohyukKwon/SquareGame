#include "stdafx.h"
#include "Path.h"
#include <string.h>
#include "String.h"
//PATH(���)�� Ư���� ������ �ִ� ��ġ�� ��Ÿ���� �ּ��̴�, Windows���� PATH��� �̸��� ȯ�溯���� �ִ�.
bool Path::ExistFile(string path)//������ ������ �ִ��� Ȯ���Ѵ�.
{
	return ExistFile(String::ToWString(path));
}
//wstring = �ѱ� ���ڿ��� ������ �ִ� ���, c��� = w_char �� ǥ���Ѵ�.
bool Path::ExistFile(wstring path)
{//GetFileAttributes() = �� �Լ��� �����̳� ������ �Ӽ��� �˾ƺ��� �뵵�̴�.(�б�����,�������� ���), ������ ���°�� INVALID_FILE_ATTRIBUTES(-1)�� �����Ѵ�.
	DWORD fileValue = GetFileAttributes(path.c_str()); // c_str = ipfilename �̴�. (IpFileName = ������ϰ�� �̸��� ������ȴ�)

	return fileValue < 0xFFFFFFFF; // 0xFFFFFFFF = 16�����ǰ��̴�. 2������ ��ȯ�ϸ� "-1"�ǰ��� ������.
}// �� -1���� ������ ���� �����Ѵ�.

bool Path::ExistDirectory(string path) 
{//ExistDirectory = ������ ��ΰ� ��ũ�� �ִ� ���� ���͸��� �����ϴ��� Ȯ���ϴ°�.
	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(wstring path)
{//���� ����. �ٸ� String�� �ƴ� wstring�� ��������ν�, �ѱ۹��ڿ��� �������ִ� 
	DWORD attribute = GetFileAttributes(path.c_str()); //DWORD = unsigned long �̰�, 4����Ʈ�� ���� �ڷ����̴�.
 //BOOL = int�̰�, 4����Ʈ�� ���� �ڷ����̴�. bool = char,1byte   //WORD = unsigned short �̰�, 2����Ʈ�� ���� �ڷ����̴�.
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && //GetFileAttributes �Ӽ���, INVALID_FILE_ATTRIBUTES && �� ���������� ���Ѵ�.
		(attribute & FILE_ATTRIBUTE_DIRECTORY)); // �Ӽ� �� ����

	return temp == TRUE; // �Ű����� ������ �۵��Ǹ� ����Ǹ� ���ϵȴ�.
}

string Path::Combine(string path1, string path2) // �� ���ڿ��� �� ���(string)�� �����Ѵ�.
{
	return path1 + path2;  // �� ���ڿ��� �ϳ��� ��ģ �ϳ��� ��θ� �����Ѵ�.
}

wstring Path::Combine(wstring path1, wstring path2) // �� ���ڿ��� �� ���(wstring)�� �����Ѵ�.
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths) //���ڿ�(string)�� �����ϴ� vector�� �ϳ��� ��η� �����Ѵ�.
{
	string temp = ""; // �����Լ� temp �� " " �� ����.
	for (string path : paths)
		temp += path; // path = temp + path�� ���� ���Ѵ�.

	return temp; // " " ���� �����Ѵ�.
}

wstring Path::Combine(vector<wstring> paths) // ���ڿ�(string)�� �����ϴ� vector�� �ϳ��� ��η� �����Ѵ�.
{
	wstring temp = L""; //���̵� ���ڿ��� ����� �ۼ��ϱ����ؼ� ���� ��� �տ� L�� ���δ�. wstring�� ���̵� ���ڿ��̱⶧���� ���ھտ� L�� ���δ�.
	for (wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(string path) // ������ ��δ� string path �̴�.
{//GetDirectoryName �Լ��� ����ϸ� ������ ��ο� ���͸� ������ ��ȯ�Ѵ�.
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
{//GetExtension �Լ��� ������ ��� ���ڿ��� Ȯ���(��ħǥ "." ����) �� ��ȯ�Ѵ�. 
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
{//GetFileName �Լ��� ������ ��� ���ڿ����� ���� �̸���,Ȯ����� ��ȯ�Ѵ�.
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
{//GetFileNameWithoutExtension �Լ��� Ȯ��� ���� ������ ��� ���ڿ��� "���� �̸�"�� ��ȯ�Ѵ�.
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

//���͸� = �������ʴ°��� �ɷ����°�.
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";  //Image
const WCHAR* Path::BinModelFilter = L"Binary Model\0*.model"; //BinModel 
const WCHAR* Path::FbxModelFilter = L"Fbx Model\0*.fbx;*.obj\0"; //FbxModel
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl"; //ShaderFileter = ���͸��Ǵ� ��ü�� ���̴��� �����Ͽ� ���͸� �����Ų��. ���͸��� ��ü�� ���̴��� ���� �Է����� ���ǰ� �� ���̴� ����� ���� ����� �ȴ�.

void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{//OpenFileDialog() = ����ڰ� ������ ������ ��û�ϴ� ǥ�� ��ȭ ���ڸ� ǥ��. �� Ŭ������ ��� �� �� ����.
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
	ofn.lpstrFileTitle = L"�ҷ�����";
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
{//SaveFileDialog() = ���� �����ȭ ���ڸ� ǥ���ϰ� ����ڰ� ������ ������ �����ϴ� �޼��带 ȣ���Ѵ�.
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
	ofn.lpstrFileTitle = L"�����ϱ�";
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
{//CreateFolder() = ��������
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
