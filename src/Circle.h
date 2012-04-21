#ifndef _CIRCLE_H_
#define _CIRCLE_H_

struct TCircle  // TODO? выделить в отдельный файл
{
	// Хранилище состояния круга. Реализует только самые примитивные операции.
	// TODO: разбить на два класса. Написать, что по-хорошему, класс игрового мира
	// (в нашем случае CCircleSet) должен работать с базовыми объектами.
	// Но это потребует использование smart pointer'ов

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
	int color;    // TODO: COLORREF

	TCircle();
	void Update(double dt);
};

#endif 