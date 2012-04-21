#include "CircleSet.h"

inline double sqr(double v)  
{ 
	return v * v;
}


CCircleSet::CCircleSet()
{
}

CCircleSet::~CCircleSet()
{
}

void CCircleSet::SetFieldHeight(double fieldHeight)
{
	m_fieldHeight = fieldHeight;
}

void CCircleSet::Add(const TCircle& circle)
{
	m_circles.push_back(circle);
}

void CCircleSet::MoveAll(double dt)
{
	TCircleList::iterator it, nextIt;

	for (it = m_circles.begin(), nextIt = it; it != m_circles.end(); it = nextIt)
	{
		nextIt++;

		TCircle& circle = *it;

		circle.Update(dt);
		if (circle.state == TCircle::csDisappeared)
			m_circles.erase(it);
	}
}

const CCircleSet::TCircleList& CCircleSet::GetCurCircles() const
{
	return m_circles;
}

bool CCircleSet::BlowCircleAtPoint(TCircle& blownCircle, double x, double	 y)
{
	  // Проверяем начиная с последних т.к. они рисуются сверху
	for (TCircleList::reverse_iterator it = m_circles.rbegin(); it != m_circles.rend(); it++)
	{
		TCircle& circle = *it;

		if (circle.state != TCircle::csFalling)
			continue;

		  // Относительно быстрое отсечение. Пригодится при тысячах кружков
		if (circle.x - circle.radius > x || circle.x + circle.radius < x)
			continue;

		if (sqr(circle.x - x) + sqr(circle.y - y) < sqr(circle.radius))
		{
			circle.state = TCircle::csBlowing;
			circle.curStateTime = 0;
			blownCircle = circle;
			return true;
		}
	}

	return false;
}