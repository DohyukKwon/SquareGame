#pragma once

class String
{
public:
	static void SplitString(vector<string>* result, string origin, string tok); // ���ڿ� origin, tok �� ������ ���ڿ��� �����ϴ� ���Ϳ� ������� �����Ѵ�.
	static void SplitString(vector<wstring>* result, wstring origin, wstring tok); //���̵� ���ڿ��̸� ���� �����ϴ�.

	static bool StartsWith(string str, string comp); // ���ڿ� comp�� �����ϴ��� Ȯ���Ͽ� ����� true �Ǵ� false �� ��ȯ�Ѵ�.
	static bool StartsWith(wstring str, wstring comp);

	static bool Contain(string str, string comp); //���ڿ� �ȿ� comp�� ���ԵǾ��ִ��� Ȯ���Ѵ�.
	static bool Contain(wstring str, wstring comp);

	static void Replace(string* str, string comp, string rep); // ���ڿ��ȿ� comp�� rep���� ġȯ�Ѵ�.
	static void Replace(wstring* str, wstring comp, wstring rep);

	static wstring ToWString(string value);  // string value �� ���� ���ڿ��� ����� �����Ѵ�.
	static string ToString(wstring value);
};

/*
Split = ���ڿ��� �����°�. Ÿ ������ ���ڿ��� ������ Split �Լ��� ����������, c++ �� �������� �ʴ´�.

SplitString() = ��Ʈ�� ���ڿ��� ������.

StartsWith() = �޼ҵ�� � ���ڿ��� Ư�� ���ڷ� �����ϴ��� Ȯ���Ͽ� ����� true Ȥ�� false �� ��ȯ�Ѵ�.

---���� ����---
Contain() = ������ �� ��Ģ�� ����Ͽ�, �� ���ڿ� ������ ������ ���ڰ� ǥ�õǴ��� ��Ÿ���� ���� ��ȯ�Ѵ�.
Include = ��ó���� ���� �ַ� �������� �ؿ� ����������� ��� ����.

�� : Contain �ڿ� ������ ����� �����̴�. ex. the bottle contains peanuts. = ������ ����ִ�.
     Include �ڿ� ������ ����� �Ϻ��̴�.     the bottle includes peanuts. = ������ ���Եƴ�.
--------------

Replace() = ���ڿ��� �Ϻθ� �ٸ� ���ڿ��� ġȯ�Ѵ�. 

ToString() = ��ü�� �������ִ� ������ ������ ���ڿ��� ����� �����ϴ� �޼ҵ��̴�.

*/