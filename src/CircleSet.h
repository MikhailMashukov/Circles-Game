#ifndef _CIRCLESET_H_
#define _CIRCLESET_H_

#include "Circle.h"
#include <list>

class CCircleSet
{
	// ����������, ���� ����� - ���������� �������� ����

public:
	typedef std::list<TCircle> TCircleList;

	CCircleSet();
	virtual ~CCircleSet();

	void SetFieldHeight(double fieldHeight);
	double GetFieldHeight() const  {  return m_fieldHeight;  }
	void Add(const TCircle& circle);
	bool BlowCircleAtPoint(TCircle& blownCircle, double x, double y);
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

protected:
	double m_fieldHeight;
	TCircleList m_circles;
};

#endif  // _CIRCLESET_H_