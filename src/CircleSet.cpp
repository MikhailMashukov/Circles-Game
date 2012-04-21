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
	for (TCircleList::iterator it = m_circles.begin(); it != m_circles.end(); it++)
	{
		TCircle& circle = *it;

		circle.Update(dt);


	}
}

const CCircleSet::TCircleList& CCircleSet::GetCurCircles() const
{
	return m_circles;
}

const CCircleSet::TCircleList& CCircleSet::GetDeletedCircles() const
{
	return m_deletedCircles;
}