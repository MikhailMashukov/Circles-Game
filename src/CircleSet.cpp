#include "CircleSet.h"

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

