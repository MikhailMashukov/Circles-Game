#ifndef _CIRCLESET_H_
#define _CIRCLESET_H_

#include <list>

struct TCircle  // TODO? �������� � ��������� ����
{
	// ������� ��������� ��������� �����.
	// TODO: ������� �� ��� ������. ��������, ��� ��-��������, ����� �������� ����
	// (� ����� ������ CCircleSet) ������ �������� � �������� ���������.
	// �� ��� ��������� ������������� smart pointer'��

	enum TState
	{
		csFalling,
		csBlowing,       // �� ����� �������� � �� ����������
		csDisappearing   // ���� ����� �� ���� � ��������
	};

	TState state;
	double curStateTime;   // ������� ������ ���� ��������� � ������� ���������.
	                       // ������������ ������ ��� ��������� csBlowing � csDisappearing
  double x, y;           // ���������� ������. 
	                       // ������� ������� ��������� � ����� ����������� -
	                       // ������ �������� � ����� ������ ����� � ������ ���������
	                       // � �������� 1
	double radius;
	double speedY;
	int color;    // TODO: COLORREF
};


class CCircleSet
{
	// ����������, ���� ����� - ���������� �������� ����

public:
	typedef std::list<TCircle> TCircleList;

	CCircleSet();
	virtual ~CCircleSet();

	// TODO? void SetAspectRatio   ��-��������, ��� ��������� ������� ����, 
	// ������ �������� ����������� ������ �������� ����, ������ ������ ��������
	// �������� ������ ��� �����... ���� � ��� ������� ���� ����������
	void Add(const TCircle& circle);
//	bool AddRandomCircle(double sizeMult = 1, double speedMult = 1);
	            // CCircleSet ����� ���� ������ ���������� ������ ������� ������ ������,
	            // � ��� ��������, �� ��� ���������� ���������� ��������� �� ���� ����,
	            // ���� ����������� �������� �� ��������� ����� ������ 
	            // � ������� ����������
	void MoveAll(double dt);
	            // ������� ��������� ����� �� speed * dt,
	            // ������ ������ ��������� ��� ������������� � 
	            // ���������� �����, ��� ������� ��������� �������� �������� 
	            // ������������, � ������ ��������
	const TCircleList& GetCurCircles() const;
	            // ��� ������� ������������� ������ �������������� � ������-�� 
	            // ����������� ��� ��������� ����������� ��������� �������� 
	            // �������.
	            // ������ ������� �� ������ ������ ������� ������ CCircleSet �
	            // ���������� ������� CCircleSet
	const TCircleList& GetDeletedCircles() const;
	            // ������ �����, �������� �� ��������� ���� (������ MoveAll)
	            // ������ ������� �� ������ ������ ������� ������ CCircleSet �
	            // ���������� ������� CCircleSet

protected:
	TCircleList m_circles, m_deletedCircles;
};

#endif  // _CIRCLESET_H_