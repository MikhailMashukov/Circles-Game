#ifndef _CIRCLESET_H_
#define _CIRCLESET_H_

#include "Circle.h"
#include <list>

class CCircleSet
{
	// Фактически, этот класс - реализация игрового мира

public:
	typedef std::list<TCircle> TCircleList;

	CCircleSet();
	virtual ~CCircleSet();

	void SetFieldHeight(double fieldHeight);
	double GetFieldHeight() const  {  return m_fieldHeight;  }
	void Add(const TCircle& circle);
	bool BlowCircleAtPoint(TCircle& blownCircle, double x, double y);
	void MoveAll(double dt);
	            // Двигает имеющиеся круги на speed * dt,
	            // меняет кругам состояние при необходимости и 
	            // перемещает круги, для которых полностью показана анимация 
	            // исчезновения, в список удалённых
	const TCircleList& GetCurCircles() const;
	            // Нет никакой необходимости сейчас заморачиваться с какими-то 
	            // итераторами или сокрытием внутреннего состояния объектов 
	            // кружков.
	            // Ссылка валидна до вызова любого другого метода CCircleSet и
	            // удалеления объекта CCircleSet

protected:
	double m_fieldHeight;
	TCircleList m_circles;
};

#endif  // _CIRCLESET_H_