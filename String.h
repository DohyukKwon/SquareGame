#pragma once

class String
{
public:
	static void SplitString(vector<string>* result, string origin, string tok); // 문자열 origin, tok 을 나누고 문자열을 저장하는 벡터에 결과값을 저장한다.
	static void SplitString(vector<wstring>* result, wstring origin, wstring tok); //와이드 문자열이며 위와 동일하다.

	static bool StartsWith(string str, string comp); // 문자열 comp로 시작하는지 확인하여 결과를 true 또는 false 로 반환한다.
	static bool StartsWith(wstring str, wstring comp);

	static bool Contain(string str, string comp); //문자열 안에 comp가 포함되어있는지 확인한다.
	static bool Contain(wstring str, wstring comp);

	static void Replace(string* str, string comp, string rep); // 문자열안에 comp를 rep으로 치환한다.
	static void Replace(wstring* str, wstring comp, wstring rep);

	static wstring ToWString(string value);  // string value 의 값을 문자열로 만들어 리턴한다.
	static string ToString(wstring value);
};

/*
Split = 문자열을 나누는것. 타 언어에서는 문자열을 나누는 Split 함수가 존재하지만, c++ 은 존재하지 않는다.

SplitString() = 스트링 문자열을 나눈다.

StartsWith() = 메소드는 어떤 문자열이 특정 문자로 시작하는지 확인하여 결과를 true 혹은 false 로 반환한다.

---이해 돕기---
Contain() = 지정된 비교 규칙을 사용하여, 이 문자열 내에서 지정한 문자가 표시되는지 나타내는 값을 반환한다.
Include = 전처리기 사용시 주로 쓰이지만 밑에 예를들기위해 잠시 나옴.

팁 : Contain 뒤에 나오는 목적어가 전부이다. ex. the bottle contains peanuts. = 땅콩이 들어있다.
     Include 뒤에 나오는 목적어가 일부이다.     the bottle includes peanuts. = 땅콩이 포함됐다.
--------------

Replace() = 문자열의 일부를 다른 문자열로 치환한다. 

ToString() = 객체가 가지고있는 정보나 값들을 문자열로 만들어 리턴하는 메소드이다.

*/