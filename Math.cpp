#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f; //const ����� �̿��Ͽ� ���̰��� �������ʵ��� ����.

float Math::Modulo(float val1, float val2) //������������ "modulo" ����Ѵ�
{//ex. 7 mod 2 = 1�̴�. why? 7�� 2�� ������ ���� 3�̰�, �������� 1�̹Ƿ� �� ���������� ��ⷯ ������ ������̵ȴ�.
	while (val1 - val2 >= 0) //val1 -val2�ǰ��� 0���� ũ�ų�������
		val1 -= val2; // val1�� ���� val1 - val2 �� ���̴�.

	return val1; // val1 �� ���� �����Ѵ�.
}

float Math::ToRadian(float degree) //sin,cos,tan �Ű������� �����̶�� �����޴´�.
{//�����̶�? 60�й�(90��,180�� ���)���� �ٸ����� �����̸� 60�й��� ���Ȱ����� �����Ϸ��� (60�й�) * PI/180 �̴�.
	return degree * PI / 180.0f;
}

float Math::ToDegree(float radian) //degree = 60��-> "��"�� ǥ���Ѵ�.
{
	return radian * 180.0f / PI; //�������� ����ϴ¹���� ���� degree�� ���ϴ¹��̴�.
}

float Math::Random(float r1, float r2)  // �����Ѱ� r1, r2�� ���Ұ��̴�.
{
	float random = ((float)rand()) / (float)RAND_MAX; //rand �Լ��� �̿��Ͽ� ���� �������� ����.
	float diff = r2 - r1; // diff = r2 - r1 ���̴�.
	float val = random * diff; //���� random x diff ���̴�.
	
	return r1 + val; // r1�� + val �� ��ģ���� �����Ѵ�.
}

float Math::Clamp(float value, float min, float max) // clamp�� ũ�⸦ �������ش�, �� �־������� [min,max]���̷� ���ΰ� ������ ����ϴ� �Լ�.
{ //ex. �־����� < min => min ��ȯ, �־����� > max => max ��ȯ, �Ѵٰ� �ƴϸ� �־����� ��ȯ
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}

int Math::Random(int r1, int r2) //���� �Ű��������� �� r1, r2 ��ȯ�ڷ��� ����
{
	return (int)(rand() % (r2 - r1 + 1)) + r1; //������ r2���� r1�� �A ���� ���Ѵ�.
}