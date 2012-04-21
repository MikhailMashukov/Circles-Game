#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <Windows.h>

struct TCircle 
{
	// Хранилище состояния круга. Реализует только самые примитивные операции.
	// TODO: разбить на два класса и закрыть свободный доступ к содержимому.
	// По-хорошему, класс игрового мира
	// (в нашем случае CCircleSet) должен работать с базовыми объектами,
	// а объекты классов-потомков - знать про OpenGL и уметь себя рисовать.
	// Однако это усложнит код, потребует использование smart pointer'ов и т.п.
	// В данном случае проще и удобнее оставить рисование в PlayState.cpp.

	static const double c_blowTime;       // Время взрыва и 
  static const double c_disappearTime;  // исчезновения круга, в секундах

	enum TState
	{
		csFalling,
		csBlowing,           // По кругу кликнули и он взрывается
		csDisappearing,      // Круг дошёл до низа и исчезает
		csDisappeared
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
	COLORREF color; 

	TCircle();
	void Update(double dt);
};

#endif 