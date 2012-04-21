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
//	bool AddRandomCircle(double sizeMult = 1, double speedMult = 1);
	            // CCircleSet имеет свою логику случайного выбора размера нового кружка,
	            // и его скорости, но для реализации увеличения сложности по ходу игры,
	            // есть возможность повлиять на результат этого выбора 
	            // с помощью множителей
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
	const TCircleList& GetDeletedCircles() const;
	            // Выдать круги, удалённые на последнем шаге (вызове MoveAll)
	            // Ссылка валидна до вызова любого другого метода CCircleSet и
	            // удалеления объекта CCircleSet

protected:
	double m_fieldHeight;
	TCircleList m_circles, m_deletedCircles;
};

#endif  // _CIRCLESET_H_