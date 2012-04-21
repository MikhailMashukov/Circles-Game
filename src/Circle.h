#ifndef _CIRCLE_H_
#define _CIRCLE_H_

struct TCircle  // TODO? �������� � ��������� ����
{
	// ��������� ��������� �����. ��������� ������ ����� ����������� ��������.
	// TODO: ������� �� ��� ������. ��������, ��� ��-��������, ����� �������� ����
	// (� ����� ������ CCircleSet) ������ �������� � �������� ���������.
	// �� ��� ��������� ������������� smart pointer'��

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
	int color;    // TODO: COLORREF

	TCircle();
	void Update(double dt);
};

#endif 