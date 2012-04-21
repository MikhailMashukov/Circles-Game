#include "CircleSet.h"

CCircleSet::CCircleSet()
{
}

CCircleSet::~CCircleSet()
{
}

void CCircleSet::Add(const TCircle& circle)
{
	m_circles.push_back(circle);
}

void CCircleSet::MoveAll(double dt)
{
}

const CCircleSet::TCircleList& CCircleSet::GetCurCircles() const
{
	return m_circles;
}

const CCircleSet::TCircleList& CCircleSet::GetDeletedCircles() const
{
	return m_deletedCircles;
}