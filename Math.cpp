#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f; //const 상수를 이용하여 파이값은 변하지않도록 고정.

float Math::Modulo(float val1, float val2) //나머지연산을 "modulo" 라고한다
{//ex. 7 mod 2 = 1이다. why? 7을 2로 나누면 몫이 3이고, 나머지가 1이므로 이 나머지값이 모듈러 연산의 결과값이된다.
	while (val1 - val2 >= 0) //val1 -val2의값이 0보다 크거나같을때
		val1 -= val2; // val1의 값은 val1 - val2 의 값이다.

	return val1; // val1 의 값을 리턴한다.
}

float Math::ToRadian(float degree) //sin,cos,tan 매개변수로 라디안이라는 값을받는다.
{//라디안이란? 60분법(90도,180도 등등)과는 다른각도 단위이며 60분법을 라디안각으로 변경하려면 (60분법) * PI/180 이다.
	return degree * PI / 180.0f;
}

float Math::ToDegree(float radian) //degree = 60˚-> "도"를 표시한다.
{
	return radian * 180.0f / PI; //라디안으로 계산하는방법을 통해 degree를 구하는법이다.
}

float Math::Random(float r1, float r2)  // 랜덤한값 r1, r2를 구할것이다.
{
	float random = ((float)rand()) / (float)RAND_MAX; //rand 함수를 이용하여 값을 무작위로 설정.
	float diff = r2 - r1; // diff = r2 - r1 값이다.
	float val = random * diff; //값은 random x diff 값이다.
	
	return r1 + val; // r1값 + val 의 합친값을 리턴한다.
}

float Math::Clamp(float value, float min, float max) // clamp는 크기를 제한해준다, 즉 주어진값을 [min,max]사이로 가두고 싶을때 사용하는 함수.
{ //ex. 주어진값 < min => min 반환, 주어진값 > max => max 반환, 둘다가 아니면 주어진값 반환
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}

int Math::Random(int r1, int r2) //랜덤 매개변수선언 및 r1, r2 반환자료형 선언
{
	return (int)(rand() % (r2 - r1 + 1)) + r1; //랜덤값 r2에서 r1을 뺸 값을 구한다.
}