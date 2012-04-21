#ifndef _CIRCLESET_H_
#define _CIRCLESET_H_

#include <list>

struct TCircle  // TODO? выделить в отдельный файл
{
	// Простое хранилище состояния круга.
	// TODO: разбить на два класса. Написать, что по-хорошему, класс игрового мира
	// (в нашем случае CCircleSet) должен работать с базовыми объектами.
	// Но это потребует использование smart pointer'ов

	enum TState
	{
		csFalling,
		csBlowing,           // По кругу кликнули и он взрывается
		csDisappearing       // Круг дошёл до низа и исчезает
	};

	TState state;
	double curStateTime;   // Сколько секунд круг находится в текущем состоянии.
	                       // Используется только для состояний csBlowing и csDisappearing
  double x, y;           // Координаты центра. 
	                       // Игровые объекты находятся в своих координатах -
	                       // внутри прямоугольника с левым нижним углом в центре координат,
	                       // шириной 1 и высотой fieldHeight
	double radius;
	double speedY;
	int color;    // TODO: COLORREF
};


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