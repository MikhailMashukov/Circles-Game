#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <Windows.h>

struct TCircle 
{
	// ��������� ��������� �����. ��������� ������ ����� ����������� ��������.
	// TODO: ������� �� ��� ������ � ������� ��������� ������ � �����������.
	// ��-��������, ����� �������� ����
	// (� ����� ������ CCircleSet) ������ �������� � �������� ���������,
	// � ������� �������-�������� - ����� ��� OpenGL � ����� ���� ��������.
	// ������ ��� �������� ���, ��������� ������������� smart pointer'�� � �.�.
	// � ������ ������ ����� � ������� �������� ��������� � PlayState.cpp.

	static const double c_blowTime;       // ����� ������ � 
  static const double c_disappearTime;  // ������������ �����, � ��������

	enum TState
	{
		csFalling,
		csBlowing,           // �� ����� �������� � �� ����������
		csDisappearing,      // ���� ����� �� ���� � ��������
		csDisappeared
	};

	TState state;
	double curStateTime;   // ������� ������ ���� ��������� � ������� ���������.
	                       // ������������ ������ ��� ��������� csBlowing � csDisappearing
  double x, y;           // ���������� ������. 
	                       // ������� ������� ��������� � ����� ����������� -
	                       // ������ �������������� � ����� ������ ����� � ������ ���������,
	                       // ������� 1 � ������� fieldHeight
	double radius;
	double speedY;
	COLORREF color; 

	TCircle();
	void Update(double dt);
};

#endif 